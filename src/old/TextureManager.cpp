#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

#include "../include/TextureManager.h"
#include "../include/glad/glad.h"
#include <iostream>
#include <string>

TextureManager gTextureManager;

std::string textureBaseDir = "assets/textures/";

GLuint TextureManager::loadTexture(const std::string &texPath) {
  int width, height, nrChannels;
  std::string path = textureBaseDir + texPath;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

  if (!data) {
    std::cerr << "Failed to load texture: " << path << std::endl;
    return 0;
  }

  GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_image_free(data);

  std::cout << "Loaded texture: " << path << std::endl;

  return textureID;
}

GLuint TextureManager::loadCubemap(const std::vector<std::string> &faces) {
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrChannels;
  for (unsigned int i = 0; i < faces.size(); i++) {
    std::string facePath = textureBaseDir + faces[i];
    unsigned char *data =
        stbi_load(facePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      GLenum format = GL_RGB;
      if (nrChannels == 4)
        format = GL_RGBA;

      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height,
                   0, format, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cerr << "Cubemap texture failed to load at path: " << faces[i]
                << std::endl;
      stbi_image_free(data);
    }
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  for (unsigned int i = 0; i < faces.size(); i++) {
    std::cout << "Loaded cubemap texture: " << faces[i] << std::endl;
  }

  return textureID;
}

GLuint TextureManager::getTexture(const std::string &name) {
  if (textures.find(name) == textures.end()) {
    std::cerr << "Texture not found: " << name << std::endl;
    return 0;
  }

  return textures[name];
}

void TextureManager::cleanup() {
  for (auto &[path, tex] : textures)
    glDeleteTextures(1, &tex);

  textures.clear();
}
