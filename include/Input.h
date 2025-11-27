#pragma once

#include "Window.h"

#include "Key.h"
#include <GLFW/glfw3.h>
#include <array>

class Input {
public:
  explicit Input(Window &window);

  void update();
  void endFrame();

  bool isKeyDown(Key key) const;
  bool isKeyPressed(Key key) const;
  bool isKeyReleased(Key key) const;

private:
	// non onwing instance
  Window *m_window;

  static constexpr int MAX_KEYS = GLFW_KEY_LAST + 1;
  std::array<bool, MAX_KEYS> m_pressed{};
  std::array<bool, MAX_KEYS> m_released{};
  std::array<bool, MAX_KEYS> m_held{};

  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);
  static int toGLFWKey(Key key);
};
