#pragma once

#include "Shader.h"
#include <memory>
#include <string>
#include <unordered_map>

class ShaderManager {
public:
  static void loadShader(const std::string &name, const std::string &vertexPath,
                         const std::string &fragmentPath);

  static Shader &getShader(const std::string &name);

  template <typename T>
  static void setUniform(const std::string &shaderName,
                         const std::string &uniformName, const T &value);

private:
  static std::unordered_map<std::string, std::unique_ptr<Shader>> s_shaders;
};
