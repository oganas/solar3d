#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

class Shader {
public:
	Shader() {};
  Shader(const std::string &vertexPath, const std::string &fragmentPath);
  ~Shader();

  void bind() const;
  void unbind() const;

  GLuint getId() const;

  // overloaded uniform setters
  void setUniform(const std::string &name, int value);
  void setUniform(const std::string &name, float value);
  void setUniform(const std::string &name, const glm::vec2 &value);
  void setUniform(const std::string &name, const glm::vec3 &value);
  void setUniform(const std::string &name, const glm::vec4 &value);
  void setUniform(const std::string &name, const glm::mat4 &value);

private:
  GLuint m_Id = 0;
  std::unordered_map<std::string, GLint> m_uniformCache;

  GLint getUniformLocation(const std::string &name);
  std::string readFile(const std::string &path);
  GLuint compileShader(GLenum type, const std::string &source);
};
