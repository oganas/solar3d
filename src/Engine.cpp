#include "Engine.h"
#include <chrono>

void Engine::run(int width, int height, const std::string &title) {
  Window w(width, height, title);
  Input i(w);

  m_window = &w;
  m_input = &i;

  start();

  auto last = std::chrono::high_resolution_clock::now();

  while (m_window->update()) {
    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;

    m_input->update();
    update(dt);
    m_input->endFrame();
  }

  delete m_window;
  delete m_input;
}

// window api implementation
void Engine::setWindowBackgroundColour(glm::vec4 colour) {
  m_window->setBackgroundColour(colour);
}

// input api implementation

// shader api implementation
void Engine::loadShader(const std::string &name, const std::string &vertexPath,
                        const std::string &fragmentPath) {
  m_shaderManager.loadShader(name, vertexPath, fragmentPath);
}

template <typename T>
void Engine::setShaderUniform(const std::string &shaderName,
                              const std::string &uniform, const T &value) {
  m_shaderManager.setUniform(shaderName, uniform, value);
}
