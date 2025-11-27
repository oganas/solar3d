#pragma once

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Window {
public:
  using RenderCallback = std::function<void(Window *)>;

  Window(int width, int height, const std::string &title);
	~Window();

  static void pollGlobalEvents();

  bool update();
  void setRenderCallback(RenderCallback cb);
  void onRender();
  void makeContextCurrent();
  void swapBuffers();
  void clear();
  void setBackgroundColour(float r, float g, float b, float a);
  bool shouldClose() const;
  GLFWwindow *getWindow() const { return m_window; }

private:
  GLFWwindow *m_window = nullptr;
  RenderCallback m_renderCallback;

  float m_clearR = 0.0f, m_clearG = 0.0f, m_clearB = 0.0f, m_clearA = 1.0f;
};
