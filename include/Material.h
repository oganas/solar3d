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

  unsigned int diffuseTextureId = 0;
};

namespace MaterialPresets {
const Material MATERIAL_GOLD = {glm::vec3(0.24725f, 0.1995f, 0.0745f),
                                glm::vec3(0.75164f, 0.60648f, 0.22648f),
                                glm::vec3(0.628281f, 0.555802f, 0.366065f),
                                51.2f};

const Material MATERIAL_CHROME = {
    glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.40f, 0.40f, 0.40f),
    glm::vec3(0.774597f, 0.774597f, 0.774597f), 76.8f};

const Material MATERIAL_RED_PLASTIC = {glm::vec3(0.0f, 0.0f, 0.0f),
                                       glm::vec3(0.5f, 0.0f, 0.0f),
                                       glm::vec3(0.7f, 0.6f, 0.6f), 32.0f};

const Material MATERIAL_EMERALD = {glm::vec3(0.0215f, 0.1745f, 0.0215f),
                                   glm::vec3(0.07568f, 0.61424f, 0.07568f),
                                   glm::vec3(0.633f, 0.727811f, 0.633f), 76.8f};
} // namespace MaterialPresets
