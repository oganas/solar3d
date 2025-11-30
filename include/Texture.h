#pragma once

#include <glad/glad.h>
#include <map>
#include <string>
#include <vector>

class Texture {
public:
  static std::string textureBaseDir;

  static GLuint loadTexture(const std::string &texPath);
  static GLuint loadCubemap(const std::vector<std::string> &faces);

  static GLuint getTexture(const std::string &name);

  static void cleanup();

private:
  static std::map<std::string, GLuint> textures;
};
