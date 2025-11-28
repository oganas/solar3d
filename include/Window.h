#pragma once

#include "glad/glad.h"
#include "glm/ext/vector_float4.hpp"

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
  void setBackgroundColour(glm::vec4 colour);
  bool shouldClose() const;
  GLFWwindow *getWindow() const { return m_window; }
	int getWidth() const;
	int getHeight() const;

private:
  GLFWwindow *m_window = nullptr;
  RenderCallback m_renderCallback;

	int m_width = 0;
	int m_height = 0;

  float m_clearR = 0.0f, m_clearG = 0.0f, m_clearB = 0.0f, m_clearA = 1.0f;
};
