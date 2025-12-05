#pragma once

#include "Component/Vertex.h"
#include "glad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

/*
 * Mesh class.
 * Creates mesh objects.
 * Contains the vertices and indices of a mesh.
 *
 * Used the following for help and inspiration:
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
 * !!! These functions were generated using AI. This was used as generated. !!!
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
  std::vector<unsigned int> indices;

  const float PI = 3.14159265359f;

  for (int i = 0; i <= stacks; ++i) {
    float stackAngle = PI / 2 - (float)i * (PI / stacks);
    float xy = radius * cosf(stackAngle);
    float z = radius * sinf(stackAngle);

    for (int j = 0; j <= slices; ++j) {
      float sectorAngle = (float)j * (2.0f * PI / slices);

      float x = xy * cosf(sectorAngle);
      float y = xy * sinf(sectorAngle);

      Vertex v{};
      v.position = glm::vec3(x, y, z);
      v.normal = glm::normalize(glm::vec3(x, y, z));
      v.uv = glm::vec2((float)j / slices, (float)i / stacks);
      v.tangent = glm::vec3(0);
      v.bitangent = glm::vec3(0);

      vertices.push_back(v);
    }
  }

  for (int i = 0; i < stacks; ++i) {
    int k1 = i * (slices + 1);
    int k2 = k1 + slices + 1;

    for (int j = 0; j < slices; ++j, ++k1, ++k2) {
      if (i != 0) {
        indices.push_back(k1);
        indices.push_back(k2);
        indices.push_back(k1 + 1);
      }
      if (i != (stacks - 1)) {
        indices.push_back(k1 + 1);
        indices.push_back(k2);
        indices.push_back(k2 + 1);
      }
    }
  }

  for (size_t i = 0; i < indices.size(); i += 3) {
    Vertex &v0 = vertices[indices[i]];
    Vertex &v1 = vertices[indices[i + 1]];
    Vertex &v2 = vertices[indices[i + 2]];

    glm::vec3 edge1 = v1.position - v0.position;
    glm::vec3 edge2 = v2.position - v0.position;

    glm::vec2 uv1 = v1.uv - v0.uv;
    glm::vec2 uv2 = v2.uv - v0.uv;

    float denom = uv1.x * uv2.y - uv2.x * uv1.y;
    float f = (fabs(denom) < 1e-6f) ? 1.0f : 1.0f / denom;

    glm::vec3 tangent(f * (uv2.y * edge1.x - uv1.y * edge2.x),
                      f * (uv2.y * edge1.y - uv1.y * edge2.y),
                      f * (uv2.y * edge1.z - uv1.y * edge2.z));

    glm::vec3 bitangent(f * (-uv2.x * edge1.x + uv1.x * edge2.x),
                        f * (-uv2.x * edge1.y + uv1.x * edge2.y),
                        f * (-uv2.x * edge1.z + uv1.x * edge2.z));

    v0.tangent += tangent;
    v1.tangent += tangent;
    v2.tangent += tangent;

    v0.bitangent += bitangent;
    v1.bitangent += bitangent;
    v2.bitangent += bitangent;
  }

  for (auto &v : vertices) {
    glm::vec3 T =
        glm::normalize(v.tangent - v.normal * glm::dot(v.normal, v.tangent));
    glm::vec3 B = glm::normalize(glm::cross(v.normal, T));

    v.tangent = T;
    v.bitangent = B;
  }

  return Mesh(vertices, indices);
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
