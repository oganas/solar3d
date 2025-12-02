#pragma once

#include "Object.h"
#include "Texture.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include <iostream>
#include <stb_image.h>
#include <string>
#include <vector>

/*
 * Model class.
 *
 * A model is a collection of objects. An object is a single unit or a wrapper
 * around a mesh. It can be externally loaded from a file or internally created.
 *
 * Partially inspired by:
 * https://learnopengl.com/Model-Loading/Assimp
 * https://www.youtube.com/watch?v=sP_kiODC25Q
 * https://www.mbsoftworks.sk/tutorials/opengl3/20-assimp-model-loading/
 */
class Model {
public:
  Model(const std::string &path);

  void setPosition(const glm::vec3 &position);
  void setRotation(const glm::vec3 &rotation);
  void setScale(const glm::vec3 &scale);

  glm::vec3 getPosition() const;
  glm::vec3 getRotation() const;
  glm::vec3 getScale() const;

  std::vector<Object> getObjects() const;

private:
  void loadModel(const std::string &path);
  void processNode(aiNode *node, const aiScene *scene);
  Object processMesh(aiMesh *mesh, const aiScene *scene);

  /*
   * Private because there is no reason to access it from the outside,
   * especially because they're not "main" objects, bur rather "sub-objects"
   * that make up a model.
   */
  std::vector<Object> objects;
};
