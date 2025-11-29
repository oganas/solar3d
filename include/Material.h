#pragma once

#include "glm/glm.hpp"

/*
 * Material struct.
 * Contains the material properties of an object such as textures, colours,
 * ambient, diffuse, specular, and shininess.
 */
struct Material {
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
};
