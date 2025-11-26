#pragma once

#include "Window.h"

#include "Key.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class MouseMode { NORMAL, DISABLED, HIDDEN };

class Input {
public:
  Input() = default;

  void init(Window *window);

  void resetStates();

  bool getKey(Key key) const;
  bool getKeyPress(Key key) const;
  bool getKeyRelease(Key key) const;

  bool getMouseButton(int button) const;
  bool getMouseButtonPress(int button) const;
  bool getMouseButtonRelease(int button) const;

  glm::vec2 getMousePos() const;
  glm::vec2 getMouseDelta() const;
  glm::vec2 getMouseScrollDelta() const;

  void setMouseMode(MouseMode mode);

private:
  bool m_pressed[348]{};
  bool m_released[348]{};
  bool m_mousePressed[7]{};
  bool m_mouseReleased[7]{};
  double m_mouseX = 0, m_mouseY = 0, m_prevMouseX = 0, m_prevMouseY = 0;
  double m_scrollX = 0, m_scrollY = 0;

  Window *m_window = nullptr;

  static void keyCallback(GLFWwindow *glfwWindow, int key, int scancode,
                          int action, int mods);
  static void mouseButtonCallback(GLFWwindow *glfwWindow, int button,
                                  int action, int mods);
  static void cursorPosCallback(GLFWwindow *glfwWindow, double xpos,
                                double ypos);
  static void scrollCallback(GLFWwindow *glfwWindow, double xoffset,
                             double yoffset);
};
