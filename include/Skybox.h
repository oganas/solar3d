#pragma once

#include "Mesh.h"
#include "Texture.h"
#include <glad/glad.h>
#include <string>
#include <vector>

class Skybox {
public:
  // Skybox cubemap texture.
  Texture *cubemapTexture;

	Mesh mesh;

  Skybox();

  Skybox(const std::vector<std::string> &faces);

	void draw() const;

private:

};
