#include <stdexcept>

#include "Window.h"

static bool glfwInitialised = false;

Window *Window::createWindow(int width, int height, const std::string &title) {
  if (!glfwInitialised) {
    if (!glfwInit())
      throw std::runtime_error("Failed to initialise GLFW");
    glfwInitialised = true;
  }

  // m_window hitns
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 8);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

  Window *w = new Window(width, height, title);
  return w;
}

Window::Window(int width, int height, const std::string &title) {
  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_window)
    throw std::runtime_error("Failed to create GLFW m_window");

  glfwMakeContextCurrent(m_window);

  // vsync on
  glfwSwapInterval(1);

  // load gl per context
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed to load GLAD");

  glfwSetWindowUserPointer(m_window, this);

  // per context gl state
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_TEXTURE_2D);
}

Window::~Window() {
  if (m_window)
    glfwDestroyWindow(m_window);
}

void Window::pollGlobalEvents() { glfwPollEvents(); }

bool Window::shouldClose() const { return glfwWindowShouldClose(m_window); }

void Window::makeContextCurrent() { glfwMakeContextCurrent(m_window); }

void Window::swapBuffers() { glfwSwapBuffers(m_window); }

void Window::clear() {
  glClearColor(m_clearR, m_clearG, m_clearB, m_clearA);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setRenderCallback(RenderCallback callback) {
  m_renderCallback = std::move(callback);
}

void Window::onRender() {
  if (m_renderCallback) {
    m_renderCallback(this);
  }
}

void Window::setBackgroundColour(float r, float g, float b, float a) {
  m_clearR = r;
  m_clearG = g;
  m_clearB = b;
  m_clearA = a;
}
