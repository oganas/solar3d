#pragma once

#include <glm/glm.hpp>

class Light {
public:
  glm::vec3 position;
  glm::vec3 colour;

  Light(const glm::vec3 &pos, const glm::vec3 &col)
      : position(pos), colour(col) {}
};
