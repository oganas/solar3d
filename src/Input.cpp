#include "Input.h"
#include <stdexcept>

void Input::init(Window *window) {
  if (!window) {
    throw std::runtime_error("Input::init must have a valid Window pointer");
  }
  m_window = window;
  GLFWwindow *glfwWin = m_window->getWindow();

  glfwSetWindowUserPointer(glfwWin, this);

  glfwSetKeyCallback(glfwWin, keyCallback);
  glfwSetMouseButtonCallback(glfwWin, mouseButtonCallback);
  glfwSetCursorPosCallback(glfwWin, cursorPosCallback);
  glfwSetScrollCallback(glfwWin, scrollCallback);

  glfwGetCursorPos(glfwWin, &m_prevMouseX, &m_prevMouseY);
  glfwGetCursorPos(glfwWin, &m_mouseX, &m_mouseY);
}

void Input::resetStates() {
  std::fill(std::begin(m_pressed), std::end(m_pressed), false);
  std::fill(std::begin(m_released), std::end(m_released), false);
  std::fill(std::begin(m_mousePressed), std::end(m_mousePressed), false);
  std::fill(std::begin(m_mouseReleased), std::end(m_mouseReleased), false);
  m_scrollX = 0;
  m_scrollY = 0;
}

bool Input::getKey(Key key) const {
  return glfwGetKey(m_window->getWindow(), static_cast<int>(key)) == GLFW_PRESS;
}
bool Input::getKeyPress(Key key) const {
  return m_pressed[static_cast<int>(key)];
}
bool Input::getKeyRelease(Key key) const {
  return m_released[static_cast<int>(key)];
}

bool Input::getMouseButton(int button) const {
  return glfwGetMouseButton(m_window->getWindow(), button) == GLFW_PRESS;
}
bool Input::getMouseButtonPress(int button) const {
  return m_mousePressed[button];
}
bool Input::getMouseButtonRelease(int button) const {
  return m_mouseReleased[button];
}

glm::vec2 Input::getMousePos() const {
  return {static_cast<float>(m_mouseX), static_cast<float>(m_mouseY)};
}
glm::vec2 Input::getMouseDelta() const {
  return {static_cast<float>(m_mouseX - m_prevMouseX),
          static_cast<float>(m_mouseY - m_prevMouseY)};
}
glm::vec2 Input::getMouseScrollDelta() const {
  return {static_cast<float>(m_scrollX), static_cast<float>(m_scrollY)};
}

void Input::setMouseMode(MouseMode mode) {
  int glfwMode = GLFW_CURSOR_NORMAL;
  switch (mode) {
  case MouseMode::NORMAL:
    glfwMode = GLFW_CURSOR_NORMAL;
    break;
  case MouseMode::DISABLED:
    glfwMode = GLFW_CURSOR_DISABLED;
    break;
  case MouseMode::HIDDEN:
    glfwMode = GLFW_CURSOR_HIDDEN;
    break;
  }
  glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, glfwMode);
}

// ----- GLFW Callbacks -----
void Input::keyCallback(GLFWwindow *glfwWindow, int key, int scancode,
                        int action, int mods) {
  Input *input = static_cast<Input *>(glfwGetWindowUserPointer(glfwWindow));
  if (!input)
    return;

  if (action == GLFW_PRESS)
    input->m_pressed[key] = true;
  else if (action == GLFW_RELEASE)
    input->m_released[key] = true;
}

void Input::mouseButtonCallback(GLFWwindow *glfwWindow, int button, int action,
                                int mods) {
  Input *input = static_cast<Input *>(glfwGetWindowUserPointer(glfwWindow));
  if (!input)
    return;

  if (action == GLFW_PRESS)
    input->m_mousePressed[button] = true;
  else if (action == GLFW_RELEASE)
    input->m_mouseReleased[button] = true;
}

void Input::cursorPosCallback(GLFWwindow *glfwWindow, double xpos,
                              double ypos) {
  Input *input = static_cast<Input *>(glfwGetWindowUserPointer(glfwWindow));
  if (!input)
    return;

  input->m_prevMouseX = input->m_mouseX;
  input->m_prevMouseY = input->m_mouseY;
  input->m_mouseX = xpos;
  input->m_mouseY = ypos;
}

void Input::scrollCallback(GLFWwindow *glfwWindow, double xoffset,
                           double yoffset) {
  Input *input = static_cast<Input *>(glfwGetWindowUserPointer(glfwWindow));
  if (!input)
    return;

  input->m_scrollX = xoffset;
  input->m_scrollY = yoffset;
}
