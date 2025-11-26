#pragma once

#include "glad/glad.h"
#include <string>
#include <unordered_map>
#include <vector>

class TextureManager {
public:
  GLuint loadTexture(const std::string &path);
  GLuint loadCubemap(const std::vector<std::string> &faces);

  GLuint getTexture(const std::string &name);

  void cleanup();

private:
  std::unordered_map<std::string, GLuint> textures;
};

extern TextureManager gTextureManager;
