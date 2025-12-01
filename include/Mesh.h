#pragma once

#include "Vertex.h"
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

/*
 * Mesh class.
 * Creates mesh objects.
 * Contains the vertices and indices of a mesh.
 *
 * Partially inspired by:
 * source: https://learnopengl.com/Model-Loading/Mesh
 */
class Mesh {
public:
  /*
   * Creates a new mesh instance.
   * This is the default constructor.
   */
  Mesh() = default;

  /*
   * Creates a new mesh instance.
   *
   * Parameters:
   *	vertices: Vector of vertices.
   *	indices: Vector of indices.
   */
  Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);

  /*
   * Draws the mesh.
   */
  void draw() const;

private:
  // Vertex array object.
  GLuint m_vao = 0;

  // Vertex buffer object.
  GLuint m_vbo = 0;

  // Element buffer object.
  GLuint m_ebo = 0;

  // Number of indices.
  GLuint m_indexCount = 0;
};

/*
 * Namespace containing mesh primitives such as cube, sphere, and torus.
 *
 * !!! These 3 functions were generated using AI. !!!
 */
namespace MeshPrimitives {
/*
 * Creates a cube mesh.
 *
 * Parameters:
 *	size: Size of the cube.
 *
 * Returns:
 *	A cube mesh.
 */
inline Mesh cube(float size = 1.0f) {
  float s = size * 0.5f;

  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  glm::vec3 positions[] = {{-s, -s, -s}, {s, -s, -s}, {s, s, -s}, {-s, s, -s},
                           {-s, -s, s},  {s, -s, s},  {s, s, s},  {-s, s, s},
                           {-s, -s, -s}, {-s, s, -s}, {-s, s, s}, {-s, -s, s},
                           {s, -s, -s},  {s, s, -s},  {s, s, s},  {s, -s, s},
                           {-s, s, -s},  {s, s, -s},  {s, s, s},  {-s, s, s},
                           {-s, -s, -s}, {s, -s, -s}, {s, -s, s}, {-s, -s, s}};

  glm::vec3 normals[] = {{0, 0, -1}, {0, 0, 1}, {-1, 0, 0},
                         {1, 0, 0},  {0, 1, 0}, {0, -1, 0}};

  glm::vec2 uv[] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

  for (int face = 0; face < 6; face++) {
    glm::vec3 normal = normals[face];
    for (int i = 0; i < 4; i++) {
      vertices.emplace_back(positions[face * 4 + i], normal, uv[i]);
    }
  }

  GLuint idx[] = {0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,
                  8,  9,  10, 10, 11, 8,  12, 13, 14, 14, 15, 12,
                  16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20};

  indices.assign(idx, idx + 36);

  Mesh cube(vertices, indices);

  return cube;
}

/*
 * Creates a sphere mesh.
 *
 * Parameters:
 *	radius: Radius of the sphere.
 *	stacks: Number of stacks of the sphere.
 *	slices: Number of slices of the sphere.
 *
 * Returns:
 *	A sphere mesh.
 */
inline Mesh sphere(float radius = 1.0f, int stacks = 32, int slices = 64) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  for (int i = 0; i <= stacks; i++) {
    float v = float(i) / stacks;
    float phi = glm::pi<float>() * v;

    float sinPhi = sin(phi);
    float cosPhi = cos(phi);

    for (int j = 0; j <= slices; j++) {
      float u = float(j) / slices;
      float theta = glm::two_pi<float>() * u;

      float x = radius * sinPhi * cos(theta);
      float y = radius * cosPhi;
      float z = radius * sinPhi * sin(theta);

      glm::vec3 pos(x, y, z);
      glm::vec3 normal = glm::normalize(pos);

      vertices.emplace_back(pos, normal, glm::vec2(u, 1.0f - v));
    }
  }

  for (int i = 0; i < stacks; i++) {
    for (int j = 0; j < slices; j++) {

      int first = i * (slices + 1) + j;
      int second = first + slices + 1;

      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(first + 1);

      indices.push_back(second);
      indices.push_back(second + 1);
      indices.push_back(first + 1);
    }
  }

  Mesh sphere(vertices, indices);

  return sphere;
}

/*
 * Creates a torus mesh.
 *
 * Parameters:
 *	majorRadius: Major radius of the torus.
 *	minorRadius: Minor radius of the torus.
 *	majorSegments: Number of major segments of the torus.
 *	minorSegments: Number of minor segments of the torus.
 *
 * Returns:
 *	A torus mesh.
 */
inline Mesh torus(float majorRadius = 1.0f, float minorRadius = 0.5f,
                  int majorSegments = 64, int minorSegments = 32) {
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;

  for (int i = 0; i <= majorSegments; i++) {
    float u = float(i) / majorSegments;
    float theta = glm::two_pi<float>() * u;

    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    for (int j = 0; j <= minorSegments; j++) {
      float v = float(j) / minorSegments;
      float phi = glm::two_pi<float>() * v;

      float cosPhi = cos(phi);
      float sinPhi = sin(phi);

      float x = (majorRadius + minorRadius * cosPhi) * cosTheta;
      float y = minorRadius * sinPhi;
      float z = (majorRadius + minorRadius * cosPhi) * sinTheta;

      glm::vec3 pos(x, y, z);

      glm::vec3 center(majorRadius * cosTheta, 0, majorRadius * sinTheta);
      glm::vec3 normal = glm::normalize(pos - center);

      vertices.emplace_back(pos, normal, glm::vec2(u, v));
    }
  }

  for (int i = 0; i < majorSegments; i++) {
    for (int j = 0; j < minorSegments; j++) {

      int first = i * (minorSegments + 1) + j;
      int second = first + minorSegments + 1;

      indices.push_back(first);
      indices.push_back(second);
      indices.push_back(first + 1);

      indices.push_back(second);
      indices.push_back(second + 1);
      indices.push_back(first + 1);
    }
  }

  Mesh torus(vertices, indices);

  return torus;
}
} // namespace MeshPrimitives
