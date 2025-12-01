#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

#include "Texture.h"
#include "glad.h"

#include <iostream>
#include <string>

Texture::Texture() {}

Texture::Texture(std::string name, const std::string &texturePath) {
  m_name = name;
  m_id = loadTexture(texturePath);
}

Texture::Texture(std::string name, std::vector<std::string> faces) {
  m_name = name;
  m_id = loadCubemap(faces);
}

GLuint Texture::getId() const { return m_id; }

GLuint Texture::loadTexture(const std::string &texPath) {
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

/*
 * Partially inspired by:
 * https://www.ogldev.org/www/tutorial25/tutorial25.html
 */
GLuint Texture::loadCubemap(const std::vector<std::string> &faces) {
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

void Texture::cleanup() { glDeleteTextures(1, &m_id); }
