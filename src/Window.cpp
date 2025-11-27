#include "Window.h"
#include <stdexcept>

static bool glfwInitialised = false;

Window::Window(int width, int height, const std::string &title) {
  if (!glfwInitialised) {
    if (!glfwInit())
      throw std::runtime_error("Failed to initialise GLFW");
    glfwInitialised = true;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 8);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_window)
    throw std::runtime_error("Failed to create GLFW window");

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1); // vsync

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed to load GLAD");

  glfwSetWindowUserPointer(m_window, this);

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

void Window::setRenderCallback(RenderCallback cb) {
  m_renderCallback = std::move(cb);
}

void Window::setBackgroundColour(float r, float g, float b, float a) {
  m_clearR = r;
  m_clearG = g;
  m_clearB = b;
  m_clearA = a;
}

bool Window::update() {
  pollGlobalEvents();
  if (shouldClose())
    return false;

  makeContextCurrent();
  clear();

  if (m_renderCallback)
    m_renderCallback(this);

  swapBuffers();

  return true;
}
