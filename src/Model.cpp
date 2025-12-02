#include "Model.h"

Model::Model(const std::string &path) { 
	loadModel(path); 
}

void Model::loadModel(const std::string &path) {
  Assimp::Importer importer;

  /*
   * Assimp preprocessofr flags, most importatnly the aiProcess_CalcTangentSpace
   * flag which calculates the tangent and bitangent vectors for the mesh.
   * Spent hours to find this out.
   */
  const aiScene *scene = importer.ReadFile(
      path, aiProcess_Triangulate | aiProcess_FlipUVs |
                aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cerr << "Failed to load model: " << path << "\nAssimp error: " << importer.GetErrorString() << std::endl;
    return;
  } else {
		std::cout << "Loaded model: " << path << std::endl;
	}

  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    objects.push_back(processMesh(mesh, scene));
  }
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    // Walk through the scene and process each node
    processNode(node->mChildren[i], scene);
  }
}

Object Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

	/*
	 * Iterate through the mesh's vertices and indices and store them in
	 * the vertices and indices vectors.
	 * TODO: fill tangent aaand bitangent vectors for normal mapping.
	 */
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                mesh->mVertices[i].z);
    vertex.normal = mesh->HasNormals()
                        ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                                    mesh->mNormals[i].z)
                        : glm::vec3(0.0f);

    if (mesh->mTangents && mesh->mBitangents) {
      vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y,
                                 mesh->mTangents[i].z);

      vertex.bitangent =
          glm::vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y,
                    mesh->mBitangents[i].z);
    } else {
      vertex.tangent = glm::vec3(0.0f);
      vertex.bitangent = glm::vec3(0.0f);
    }

    if (mesh->mTextureCoords[0]) {
      vertex.uv =
          glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    } else {
      vertex.uv = glm::vec2(0.0f);
    }

    vertices.push_back(vertex);
  }

	// Fill indices
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }

  Material mat;
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    aiColor3D color(0.f, 0.f, 0.f);
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    mat.diffuse = glm::vec3(color.r, color.g, color.b);

    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    mat.ambient = glm::vec3(color.r, color.g, color.b);

    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    mat.specular = glm::vec3(color.r, color.g, color.b);

    float shininess = 32.0f;
    material->Get(AI_MATKEY_SHININESS, shininess);
    mat.shininess = shininess;

    // Diffuse map
    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
      aiString str;
      material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
      std::string path = str.C_Str();

      if (!path.empty() && path[0] == '*') {
        unsigned int texIndex = std::stoi(path.substr(1));
        if (texIndex < scene->mNumTextures) {
          aiTexture *tex = scene->mTextures[texIndex];
          GLuint texID;
          glGenTextures(1, &texID);
          glBindTexture(GL_TEXTURE_2D, texID);

          // Spent hours to find this but this is for loading compressed
          // embedded textures in files like .gltf that don't rely on external
          // textures.
          if (tex->mHeight == 0) {
            int width, height, nrChannels;
            unsigned char *data = stbi_load_from_memory(
                reinterpret_cast<unsigned char *>(tex->pcData), tex->mWidth,
                &width, &height, &nrChannels, 0);

            if (data) {
              GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
              glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                           GL_UNSIGNED_BYTE, data);
              glGenerateMipmap(GL_TEXTURE_2D);
              stbi_image_free(data);
            }
          } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->mWidth, tex->mHeight,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pcData);
            glGenerateMipmap(GL_TEXTURE_2D);
          }

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                          GL_LINEAR_MIPMAP_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

          mat.diffuseTexture = new Texture();
          mat.diffuseTexture->setId(texID);
        }
      } else {
        std::string directory = "";
        std::string fullPath = directory + "/" + path;
        mat.diffuseTexture = new Texture(path, fullPath);
      }
    }

    /*
     * Normal mapping
     *
     * Check for normal map (aiTextureType_NORMALS) first, then check for
     * bump map (aiTextureType_HEIGHT) which is what's used in .obj and .mtl
     * files.
     *
     * Used the following for help:
     * https://learnopengl.com/Lighting/Normal-Mapping
     * https://www.youtube.com/watch?v=TnewxQxtoKs
     * https://www.youtube.com/watch?v=LRbgii6mVU4
     */
    aiTextureType normalMapType = aiTextureType_UNKNOWN;

    if (material->GetTextureCount(aiTextureType_NORMALS) > 0) {
      normalMapType = aiTextureType_NORMALS;
    } else if (material->GetTextureCount(aiTextureType_HEIGHT) > 0) {
      // For .obj files
      normalMapType = aiTextureType_HEIGHT;
    }

    if (normalMapType != aiTextureType_UNKNOWN) {
      aiString str;
      material->GetTexture(normalMapType, 0, &str);
      std::string path = str.C_Str();

      // External file
      if (!path.empty() && path[0] != '*') {
        mat.normalTexture = new Texture(path, path);
        mat.hasNormal = true;
      } else if (path[0] == '*') {
        /*
         * Embedded normal map, as mentioned above, used in .gltf files and also
         * .glb files I think.
         */
        unsigned int texIndex = std::stoi(path.substr(1));
        if (texIndex < scene->mNumTextures) {
          aiTexture *tex = scene->mTextures[texIndex];
          GLuint texID;
          glGenTextures(1, &texID);
          glBindTexture(GL_TEXTURE_2D, texID);

          if (tex->mHeight == 0) {
            int width, height, nrChannels;
            unsigned char *data = stbi_load_from_memory(
                reinterpret_cast<unsigned char *>(tex->pcData), tex->mWidth,
                &width, &height, &nrChannels, 0);

            if (data) {
              GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
              glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                           GL_UNSIGNED_BYTE, data);
              glGenerateMipmap(GL_TEXTURE_2D);
              stbi_image_free(data);
            }
          } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->mWidth, tex->mHeight,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pcData);
            glGenerateMipmap(GL_TEXTURE_2D);
          }

          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                          GL_LINEAR_MIPMAP_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

          mat.normalTexture = new Texture();
          mat.normalTexture->setId(texID);
          mat.hasNormal = true;
        }
      }
    } else {
      mat.hasNormal = false;
    }
  }

  Mesh m(vertices, indices);
  return Object(mesh->mName.C_Str(), m, mat);
}

void Model::setPosition(const glm::vec3 &position) {
  for (auto &obj : objects) {
    obj.setPosition(position);
  }
}

void Model::setRotation(const glm::vec3 &rotation) {
  for (auto &obj : objects) {
    obj.setRotation(rotation);
  }
}

void Model::setScale(const glm::vec3 &scale) {
  for (auto &obj : objects) {
    obj.setScale(scale);
  }
}

std::vector<Object> Model::getObjects() const { return objects; }

glm::vec3 Model::getPosition() const { return objects[0].transform.position; }

glm::vec3 Model::getRotation() const { return objects[0].transform.rotation; }

glm::vec3 Model::getScale() const { return objects[0].transform.scale; }
