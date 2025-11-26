#pragma once

#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include <functional>
#include <string>

class Window {
public:
  Window(int width, int height, const char *title);
  ~Window();

  GLFWwindow *getWindow();
	void setBackgroundColour(float r, float g, float b, float a);
	void clear();
	void pollEvents();
	void swapBuffers();
	void shouldClose();

private:
  GLFWwindow *m_window;
  int m_width, m_height;
  std::string m_title;
};
