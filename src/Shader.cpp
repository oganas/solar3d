#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
  std::string vertexSrc = readFile(vertexPath);
  std::string fragmentSrc = readFile(fragmentPath);

  GLuint vert = compileShader(GL_VERTEX_SHADER, vertexSrc);
  GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

  m_ID = glCreateProgram();
  glAttachShader(m_ID, vert);
  glAttachShader(m_ID, frag);
  glLinkProgram(m_ID);

  GLint success;
  glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
  if (!success) {
    GLint len;
    glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &len);
    std::string log(len, ' ');
    glGetProgramInfoLog(m_ID, len, nullptr, &log[0]);
    throw std::runtime_error("Shader link error: " + log);
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
}

Shader::~Shader() { glDeleteProgram(m_ID); }

void Shader::bind() const { glUseProgram(m_ID); }
void Shader::unbind() const { glUseProgram(0); }

GLint Shader::getUniformLocation(const std::string &name) {
  if (m_uniformCache.find(name) != m_uniformCache.end())
    return m_uniformCache[name];

  GLint location = glGetUniformLocation(m_ID, name.c_str());
  if (location == -1)
    std::cerr << "[Warning] Uniform '" << name << "' not found!\n";

  m_uniformCache[name] = location;
  return location;
}

void Shader::setUniform(const std::string &name, int value) {
  glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, float value) {
  glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const std::string &name, const glm::vec2 &value) {
  glUniform2fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setUniform(const std::string &name, const glm::vec3 &value) {
  glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setUniform(const std::string &name, const glm::vec4 &value) {
  glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setUniform(const std::string &name, const glm::mat4 &value) {
  glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

std::string Shader::readFile(const std::string &path) {
  std::ifstream file(path);
  if (!file)
    throw std::runtime_error("Cannot open shader file: " + path);

  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

GLuint Shader::compileShader(GLenum type, const std::string &source) {
  GLuint shader = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLint len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    std::string log(len, ' ');
    glGetShaderInfoLog(shader, len, nullptr, &log[0]);
    throw std::runtime_error("Shader compile error: " + log);
  }

  return shader;
}
