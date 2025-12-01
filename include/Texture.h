#pragma once

#include "glad.h"
#include <map>
#include <string>
#include <vector>

/*
 * Texture class.
 * Handles texture loading.
 * Layer of abstraction for handling texture related tasks.
 */
class Texture {
public:
  /*
   * Creates a new texture instance.
   * This is the default constructor.
   */
  Texture();

  /*
   * Creates a new texture instance.
   *
   * Parameters:
   * 	name: Name of the texture.
   *	textureBaseDir: Base directory for loading textures.
   */
  Texture(std::string name, const std::string &texturePath);

	/*
   * Creates a new texture instance.
   *
   * Parameters:
   * 	name: Name of the texture.
   *	faces: Vector of cubemap texture file paths.
   */
	Texture(std::string name, std::vector<std::string> faces);

	/*
   * Gets the texture's OpenGL ID.
	 *
   * Returns:
   *	The texture's OpenGL ID.
   */
	GLuint getId() const;

	/*
   * Loads a texture.
   *
   * Parameters:
   *	texPath: Path to the texture file.
   * Returns:
   *	The texture's OpenGL ID.
   */
  GLuint loadTexture(const std::string &texPath);

	/*
   * Loads a cubemap texture.
   *
   * Parameters:
   *	faces: Vector of cubemap texture file paths.
   * Returns:
   *	The cubemap texture's OpenGL ID.
   */
  GLuint loadCubemap(const std::vector<std::string> &faces);

	/*
   * Cleans up the texture.
   */
  void cleanup();

private:
  // Texture name.
  std::string m_name;

  // Texture OpenGL ID.
  GLuint m_id = 0;

  // Texture base directory for loading textures.
  std::string textureBaseDir = "assets/textures/";
};
