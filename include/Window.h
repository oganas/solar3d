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
  GLFWwindow *getWindow() const { return window; }

  ~Window();

private:
  Window(int width, int height, const std::string &title);

  GLFWwindow *window;
  RenderCallback renderCallback;

  float clearR = 0.0f;
  float clearG = 0.0f;
  float clearB = 0.0f;
  float clearA = 1.0f;
};
