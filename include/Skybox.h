#pragma once

#include "Mesh.h"
#include "Texture.h"
#include <glad/glad.h>
#include <string>
#include <vector>

/*
 * Skybox class.
 *
 * Represents a skybox background.
 */
class Skybox {
public:
  // Skybox cubemap texture.
  Texture *cubemapTexture;

  // Skybox mesh.
  Mesh mesh;

  /*
   * Creates a skybox instance.
   */
  Skybox();

  /*
   * Creates a skybox with the given faces.
   */
  Skybox(const std::vector<std::string> &faces);

  /*
   * Draws the skybox.
   */
  void draw() const;

private:
};
