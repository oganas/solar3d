#pragma once

#include "Render/Mesh.h"
#include "Render/Texture.h"
#include "glad.h"
#include <string>
#include <vector>

/*
 * Skybox class.
 *
 * Represents a skybox background.
 *
 * Used the following for help and inspiration:
 * https://www.ogldev.org/www/tutorial25/tutorial25.html
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
