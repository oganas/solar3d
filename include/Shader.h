#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

/*
 * Shader class.
 * Handles shader loading and uniform setting.
 * Layer of abstraction for handling shader related tasks.
 */
class Shader {
public:
  /*
   * Creates a new shader instance.
   * This is the default constructor.
   */
  Shader() {};

  /*
   * Creates a new shader instance.
   *
   * Parameters:
   *	vertexPath: Path to the vertex shader file.
   *	fragmentPath: Path to the fragment shader file.
   */
  Shader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);

  /*
   * Destroys the shader instance.
   */
  ~Shader();

  /*
   * Binds the shader (uses the shader's program).
   * Essentially 'glUseProgram(m_Id);'.
   */
  void bind() const;

  /*
   * Unbinds the shader (uses the shader's program).
   * Essentially 'glUseProgram(0);'.
   */
  void unbind() const;

  /*
   * Gets the shader's program ID.
   * Returns:
   *	The shader's program ID.
   */
  GLuint getId() const;

  /*
   * Sets an integer uniform value.
   *
   * Parameters:
   *	name: Name of the uniform.
   *	value: Integer value of the uniform.
   */
  void setUniform(const std::string &name, int value);

  /*
   * Sets a float uniform value.
   *
   * Parameters:
   *	name: Name of the uniform.
   *	value: Float value of the uniform.
   */
  void setUniform(const std::string &name, float value);

  /*
   * Sets a vec2 uniform value.
   *
   * Parameters:
   *	name: Name of the uniform.
   *	value: Vec2 value of the uniform.
   */
  void setUniform(const std::string &name, const glm::vec2 &value);

  /*
   * Sets a vec3 uniform value.
   *
   * Parameters:
   *	name: Name of the uniform.
   *	value: Vec3 value of the uniform.
   */
  void setUniform(const std::string &name, const glm::vec3 &value);

  /*
   * Sets a vec4 uniform value.
   *
   * Parameters:
   *	name: Name of the uniform.
   *	value: Vec4 value of the uniform.
   */
  void setUniform(const std::string &name, const glm::vec4 &value);

  /*
   * Sets a mat4 uniform value.
   *
   * Parameters:
   *	name: Name of the uniform.
   *	value: Mat4 value of the uniform.
   */
  void setUniform(const std::string &name, const glm::mat4 &value);

private:
	// Shader name.
	std::string m_name;

  // Shader program ID.
  GLuint m_id = 0;

  // Shader program uniforms cache to avoid calling 'getUniformLocation()'' for
  // every 'setUniform()' call.
  std::unordered_map<std::string, GLint> m_uniformCache;

  /*
   * Gets the uniform location of a uniform.
   *
   * Parameters:
   *	name: Name of the uniform.
   * Returns:
   *	The uniform location as a GLuint.
   */
  GLint getUniformLocation(const std::string &name);

  /*
   * Reads a file and returns its contents as a string.
   *
   * Parameters:
   *	path: Path to the file.
   * Returns:
   *	The file's contents as a string.
   */
  std::string readFile(const std::string &path);

  /*
   * Compiles a shader.
   *
   * Parameters:
   *	type: Type of the shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
   *	source: Source code of the shader.
   * Returns:
   *	The shader's ID.
   */
  GLuint compileShader(GLenum type, const std::string &source);
};
