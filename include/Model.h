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

      if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        mat.diffuseTexture = new Texture(str.C_Str(), str.C_Str());
      }
    }

    Mesh m(vertices, indices);
    return Object(mesh->mName.C_Str(), m, mat);
  }
};
