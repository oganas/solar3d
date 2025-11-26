#pragma once

#include "Window.h"

#include "Key.h"
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>

class Input {
public:
  void init(Window *window);

  void update();

  bool isKeyDown(Key key) const;

  bool isKeyPressed(Key key) const;

  bool isKeyReleased(Key key) const;

  void endFrame();

private:
  Window *m_window = nullptr;

  static constexpr int MAX_KEYS = GLFW_KEY_LAST + 1;
  std::array<bool, MAX_KEYS> m_pressed{};
  std::array<bool, MAX_KEYS> m_released{};
  std::array<bool, MAX_KEYS> m_held{};

  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static int toGLFWKey(Key key);
};
