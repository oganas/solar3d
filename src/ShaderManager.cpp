#include "ShaderManager.h"
#include <stdexcept>

std::unordered_map<std::string, std::unique_ptr<Shader>>
    ShaderManager::s_shaders;

void ShaderManager::loadShader(const std::string &name,
                               const std::string &vertexPath,
                               const std::string &fragmentPath) {
  if (s_shaders.find(name) != s_shaders.end())
    return; // already loaded

  s_shaders[name] = std::make_unique<Shader>(vertexPath, fragmentPath);
}

Shader &ShaderManager::getShader(const std::string &name) {
  auto it = s_shaders.find(name);
  if (it == s_shaders.end())
    throw std::runtime_error("Shader not loaded: " + name);

  return *it->second;
}

template <typename T>
void ShaderManager::setUniform(const std::string &shaderName,
                               const std::string &uniformName, const T &value) {
  Shader &shader = getShader(shaderName);
  shader.bind();
  shader.setUniform(uniformName, value);
  shader.unbind();
}

// explicit template instantiations for common types
template void ShaderManager::setUniform<int>(const std::string &,
                                             const std::string &, const int &);
template void ShaderManager::setUniform<float>(const std::string &,
                                               const std::string &,
                                               const float &);
template void ShaderManager::setUniform<glm::vec2>(const std::string &,
                                                   const std::string &,
                                                   const glm::vec2 &);
template void ShaderManager::setUniform<glm::vec3>(const std::string &,
                                                   const std::string &,
                                                   const glm::vec3 &);
template void ShaderManager::setUniform<glm::vec4>(const std::string &,
                                                   const std::string &,
                                                   const glm::vec4 &);
template void ShaderManager::setUniform<glm::mat4>(const std::string &,
                                                   const std::string &,
                                                   const glm::mat4 &);
