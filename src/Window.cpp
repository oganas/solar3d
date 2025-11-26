#include <stdexcept>

#include "../include/Window.h"

Window::Window(int width, int height, const char *title)
    : m_width(width), m_height(height), m_title(title), m_window(nullptr) {
  if (!glfwInit())
    throw std::runtime_error("Failed to initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 8);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!m_window)
    throw std::runtime_error("Failed to create GLFW window");

  glfwMakeContextCurrent(m_window);

  // vsync on
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed to initialize GLAD");

  glfwSetWindowUserPointer(m_window, this);

  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_TEXTURE_2D);
}

Window::~Window() { glfwTerminate(); }

GLFWwindow *Window::getWindow() { return m_window; }

void Window::setBackgroundColour(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void Window::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void Window::pollEvents() { glfwPollEvents(); }

void Window::swapBuffers() { glfwSwapBuffers(m_window); }

void Window::shouldClose() { glfwSetWindowShouldClose(m_window, true); }
