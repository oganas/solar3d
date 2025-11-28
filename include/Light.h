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

  // Colour of the light.
  glm::vec3 colour;

  /*
   * Creates a new light instance.
   *
   * Parameters:
   *	pos: Position of the light in world space.
   *	col: Colour of the light.
   */
  Light(const glm::vec3 &position, const glm::vec3 &colour)
      : position(position), colour(colour) {}
};
