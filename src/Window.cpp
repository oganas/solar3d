#include <stdexcept>

#include "../include/Window.h"

static bool glfwInitialised = false;

Window *Window::createWindow(int width, int height, const std::string &title) {
  if (!glfwInitialised) {
    if (!glfwInit())
      throw std::runtime_error("Failed to initialise GLFW");
    glfwInitialised = true;
  }

  // window hitns
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 8);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

  Window *w = new Window(width, height, title);
  return w;
}

Window::Window(int width, int height, const std::string &title) {
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window)
    throw std::runtime_error("Failed to create GLFW window");

  glfwMakeContextCurrent(window);

  // vsync on
  glfwSwapInterval(1);

  // load gl per context
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw std::runtime_error("Failed to load GLAD");

  glfwSetWindowUserPointer(window, this);

  // per context gl state
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  glEnable(GL_TEXTURE_2D);
}

Window::~Window() {
  if (window)
    glfwDestroyWindow(window);
}

void Window::pollGlobalEvents() { glfwPollEvents(); }

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

void Window::makeContextCurrent() { glfwMakeContextCurrent(window); }

void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::clear() {
  glClearColor(clearR, clearG, clearB, clearA);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setRenderCallback(RenderCallback callback) {
  renderCallback = std::move(callback);
}

void Window::onRender() {
  if (renderCallback) {
    renderCallback(this);
  }
}

void Window::setBackgroundColour(float r, float g, float b, float a) {
  clearR = r;
  clearG = g;
  clearB = b;
  clearA = a;
}
