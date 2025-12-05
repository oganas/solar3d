#include "Core/Input/Input.h"

Input::Input(Window &window) : m_window(&window) {
  GLFWwindow *glfwWin = m_window->getWindow();

  glfwSetWindowUserPointer(glfwWin, this);
  glfwSetKeyCallback(glfwWin, keyCallback);

  m_pressed.fill(false);
  m_released.fill(false);
  m_held.fill(false);
}

void Input::update() {
  // Placeholder for mouse movement state tracking or other input polling
}

bool Input::isKeyDown(Key key) const { return m_held[toGLFWKey(key)]; }

bool Input::isKeyPressed(Key key) const { return m_pressed[toGLFWKey(key)]; }

bool Input::isKeyReleased(Key key) const { return m_released[toGLFWKey(key)]; }

void Input::endFrame() {
  m_pressed.fill(false);
  m_released.fill(false);
}

void Input::keyCallback(GLFWwindow *window, int key, int scancode, int action,
                        int mods) {
  Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
  if (!input || key < 0 || key >= MAX_KEYS)
    return;

  if (action == GLFW_PRESS) {
    input->m_held[key] = true;
    input->m_pressed[key] = true;
  } else if (action == GLFW_RELEASE) {
    input->m_held[key] = false;
    input->m_released[key] = true;
  }
}

int Input::toGLFWKey(Key key) { return keyToOpenGL[static_cast<int>(key)]; }
