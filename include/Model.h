/*
#pragma once

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

class Model {
public:
  // Loads a model from the given file path
  Model(std::string path);

  // Draws all meshes in the model
  void draw() const;

  // Public collection of meshes
  std::vector<Mesh> meshes;

private:
  std::string directory;

  // Assimp processing functions
  void loadModel(std::string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  // Note: Texture loading logic will be needed here as well,
  // but we'll focus on the mesh geometry for now.
};
*/

#pragma once

#include "Object.h"
#include "Texture.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <iostream>
#include <string>
#include <vector>
#include <../external/stb/stb_image.h>

class Model {
public:
  std::vector<Object> objects;

  Model(const std::string &path) { loadModel(path); }

private:
  void loadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_FlipUVs |
                  aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
      std::cerr << "Assimp error: " << importer.GetErrorString() << std::endl;
      return;
    }

    processNode(scene->mRootNode, scene);
  }

  void processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      objects.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
      processNode(node->mChildren[i], scene);
    }
  }

  Object processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
      Vertex vertex;
      vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                  mesh->mVertices[i].z);
      vertex.normal = mesh->HasNormals()
                          ? glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                                      mesh->mNormals[i].z)
                          : glm::vec3(0.0f);

      if (mesh->mTextureCoords[0]) {
        vertex.uv = glm::vec2(mesh->mTextureCoords[0][i].x,
                              mesh->mTextureCoords[0][i].y);
      } else {
        vertex.uv = glm::vec2(0.0f);
      }

      vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
      aiFace face = mesh->mFaces[i];
      for (unsigned int j = 0; j < face.mNumIndices; j++)
        indices.push_back(face.mIndices[j]);
    }

    // Material
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

      // Handle diffuse texture
      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        std::string path = str.C_Str();

        if (!path.empty() && path[0] == '*') {
          // Embedded texture
          unsigned int texIndex = std::stoi(path.substr(1));
          if (texIndex < scene->mNumTextures) {
            aiTexture *tex = scene->mTextures[texIndex];
            // Create a Texture from memory
            GLuint texID;
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);

            if (tex->mHeight == 0) {
              // Compressed (PNG/JPG)
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
              // Uncompressed RGBA
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
          // External file
          std::string directory =
              ""; // you can extract directory from model path
          std::string fullPath = directory + "/" + path;
          mat.diffuseTexture = new Texture(path, fullPath);
        }
      }
    }

    Mesh m(vertices, indices);
    return Object(mesh->mName.C_Str(), m, mat);
  }
};
