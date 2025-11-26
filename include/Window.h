#pragma once

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class Window {
public:
  using RenderCallback = std::function<void(Window *)>;

  static Window *createWindow(int width, int height, const std::string &title);

  static void pollGlobalEvents();

  void setRenderCallback(RenderCallback cb);

  void onRender();

  void makeContextCurrent();
  void swapBuffers();
  void clear();

  void setBackgroundColour(float r, float g, float b, float a);

  bool shouldClose() const;
  GLFWwindow *getWindow() const { return m_window; }

  ~Window();

private:
  Window(int width, int height, const std::string &title);

  GLFWwindow *m_window;
  RenderCallback m_renderCallback;

  float m_clearR = 0.0f;
  float m_clearG = 0.0f;
  float m_clearB = 0.0f;
  float m_clearA = 1.0f;
};
