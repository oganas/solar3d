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
