#pragma once

#include "Window.h"

#include "Key.h"
#include <GLFW/glfw3.h>
#include <array>

/*
 * Input class.
 * Handles anything related to input.
 * This includes keyboard input, mouse input, etc.
 */
class Input {
public:
  /*
   * Uses a window instance to get key callbacks.
   */
  explicit Input(Window &window);

  /*
   *	Updates the input state.
   */
  void update();

  /*
   *	Resets the input state.
	 *	Important for all key events to be reset at the end of the loop otherwise there will be weird behaviour or they will not work.
   */
  void endFrame();

  /*
   *	Checks if a key is currently being held down.
   */
  bool isKeyDown(Key key) const;

  /*
   *	Checks if a key was just pressed.
   *	Does not check if the key is being held down.
   */
  bool isKeyPressed(Key key) const;

  /*
   *	Checks if a key was just released from being pressed.
   *	Does not check if the key is being held down.
   */
  bool isKeyReleased(Key key) const;

private:
  // Window instance belonging to this input instance.
  Window *m_window;

  // The maximum number of keys that can be pressed.
  static constexpr int MAX_KEYS = GLFW_KEY_LAST + 1;

  // Array holding the state of all keys that are currently being pressed.
  std::array<bool, MAX_KEYS> m_pressed{};

  // Array holding the state of all keys that were just released.
  std::array<bool, MAX_KEYS> m_released{};

  // Array holding the state of all keys that are currently being held down.
  std::array<bool, MAX_KEYS> m_held{};

  // key callback function for the window.
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);

  /*
   * Converts a key from my custom key enum type to a GLFW key.
   *
   * Returns -1 if the key is not a valid GLFW key.
   * Returns the GLFW key as an int if the key is a valid GLFW key.
   */
  static int toGLFWKey(Key key);
};
