#include "Model.h"
#include <iostream>

Model::Model(std::string path) { loadModel(path); }

void Model::draw() const {
  for (const auto &mesh : meshes) {
    mesh.draw();
  }
}

void Model::loadModel(std::string path) {
  // 1. Create Assimp Importer and load the scene
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      path,
      aiProcess_Triangulate |          // Ensures all primitives are triangles
          aiProcess_GenSmoothNormals | // Generates smooth normals if none exist
          aiProcess_FlipUVs | // Flips the texture coordinates (common in
                              // OpenGL)
          aiProcess_JoinIdenticalVertices // Optimizes the vertex buffer
  );

  // 2. Check for errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    std::cerr << "ASSIMP Error: " << importer.GetErrorString() << std::endl;
    return;
  }

  // 3. Extract the model's directory path for texture loading (optional for
  // now)
  directory = path.substr(0, path.find_last_of('/'));

  // 4. Recursively process the root node of the scene
  processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  // Process all the node's meshes (if any)
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    // Assimp stores mesh indices in the node, not the mesh data itself
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    meshes.push_back(processMesh(mesh, scene));
  }

  // Then process all its children nodes recursively
  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  // Process vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;

    // Positions
    vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                mesh->mVertices[i].z);

    // Normals
    if (mesh->HasNormals()) {
      vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                                mesh->mNormals[i].z);
    } else {
      // Default normal if none is provided
      vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // Texture Coordinates (Assimp supports up to 8 UV sets, we use the first
    // one)
    if (mesh->mTextureCoords[0]) {
      // Assimp uses 3 components, but we only need 2 (x and y)
      vertex.uv =
          glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    } else {
      // Default UV if none is provided
      vertex.uv = glm::vec2(0.0f, 0.0f);
    }

    vertices.push_back(vertex);
  }

  // Process indices
  // A mesh face is a primitive (like a triangle) defined by its vertices.
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  // Assimp material loading logic would go here,
  // but for simplicity, we return a Mesh with only geometry for now.

  return Mesh(vertices, indices); // Uses your existing Mesh constructor
}
