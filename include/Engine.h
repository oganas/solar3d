#pragma once

#include "Input.h"
#include "ShaderManager.h"
#include "Window.h"
#include <memory>

class Engine {
public:
  Engine() = default;
  virtual ~Engine() = default;

  void run(int width = 800, int height = 600, const std::string &title = "App");

  virtual void start() {}
  virtual void update(float dt) {}

  // window api
  void setWindowBackgroundColour(float r, float g, float b, float a);

  // input api
  bool isKeyDown(Key key) const { return m_input->isKeyDown(key); }
  bool isKeyPressed(Key key) const { return m_input->isKeyPressed(key); }
  bool isKeyReleased(Key key) const { return m_input->isKeyReleased(key); }

  // shader api
  void loadShader(const std::string &name, const std::string &vertexPath,
                  const std::string &fragmentPath);
  template <typename T>
  void setShaderUniform(const std::string &shaderName,
                        const std::string &uniform, const T &value);

private:
  Window *m_window = nullptr;
  Input *m_input = nullptr;
  ShaderManager m_shaderManager;
};
