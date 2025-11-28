#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

using namespace glm;

/*
 * Transform struct component of an object.
 * Contains the position, rotation, and scale of an object.
 */
struct Transform {
  // position of the object
  vec3 position = vec3(0.0f);

  // rotation of the object
  vec3 rotation = vec3(0.0f);

  // scale of the object
  vec3 scale = vec3(1.0f);

  /*
   * Returns the matrix of the transform.
   * This is the matrix that is used for rendering.
   */
  mat4 getMatrix() const {
    // translation
    mat4 m = translate(mat4(1.0f), position);

    // rotation
    m = rotate(m, rotation.x, vec3(1, 0, 0));
    m = rotate(m, rotation.y, vec3(0, 1, 0));
    m = rotate(m, rotation.z, vec3(0, 0, 1));

    // scale
    // for some reason can't do scale() without glm:: ??
    m = glm::scale(m, scale);

    return m;
  }
};
