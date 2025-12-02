#pragma once

#include "Colour.h"
#include "glad.h"
#include <glm/glm.hpp>
#include <vector>

using namespace glm;

/*
 * Vertex struct.
 * Contains the position, colour, normal, and uv of a vertex.
 * Used in the Mesh class.
 *
 * Partially inspired by:
 * source: https://learnopengl.com/Model-Loading/Mesh
 */
struct Vertex {
  vec3 position;
  vec3 normal;
  vec2 uv;
  vec3 tangent;
  vec3 bitangent;

  Vertex() = default;
  Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord)
      : position(position), normal(normal), uv(texCoord) {}
};

/*
 * Idk why the render bug is happening.
 *
 * position = 12 bytes because vec3
 * colour = 16 bytes because vec4
 * normal = 12 bytes because vec3
 * uv = 8 bytes because vec2
 *
 * total = 48 bytes
 *
 * When I define vec4 colour under
 * vec3 position the bug happens, when I define it under vec2 uv (all
 * the way at the bottom) it works fine, but I dont know why.
 */
static_assert(sizeof(Vertex) == 56, "Vertex struct must be tightly packed");
