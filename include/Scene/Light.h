#pragma once

#include <glm/glm.hpp>

/*
 * Light class.
 * Creates light objects.
 * Contains the position and colour of a light.
 */
class Light {
public:
  // Position of the light in world space.
  glm::vec3 position;

  // Ambient colour of the light.
  glm::vec3 ambient;

  // Diffuse colour of the light.
  glm::vec3 diffuse;

  // Specular colour of the light.
  glm::vec3 specular;

  /*
   * Creates a new light instance.
   * This is the default constructor.
   */
  Light() = default;

  /*
   * Creates a new light instance.
   *
   * Parameters:
   *	position: Position of the light in world space.
   *	ambient: Ambient colour of the light.
   *	diffuse: Diffuse colour of the light.
   *	specular: Specular colour of the light.
   */
  Light(const glm::vec3 &position, const glm::vec3 ambient,
        const glm::vec3 diffuse, const glm::vec3 specular)
      : position(position), ambient(ambient), diffuse(diffuse),
        specular(specular) {}
};
