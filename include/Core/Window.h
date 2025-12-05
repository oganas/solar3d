#pragma once

#include "glad.h"
#include "glm/ext/vector_float4.hpp"

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

/*
 * Window class.
 * Handles window creation and event handling.
 * Layer of abstraction for handling window related tasks.
 */
class Window {
public:
  /*
   * Callback function for the window.
   * Takes a pointer to the window as an argument.
   */
  using RenderCallback = std::function<void(Window *)>;

  /*
   * Creates a new window instance.
   * This is the default constructor.
   */
  Window();

  /*
   * Creates a new window instance.
   *
   * Parameters:
   *	width: Width of the window.
   *	height: Height of the window.
   *	title: Title of the window.
   */
  Window(int width, int height, const std::string &title);

  /*
   * Destroys the window instance.
   */
  ~Window();

  /*
   * Polls window events.
   */
  static void pollGlobalEvents();

  /*
   * Contains render callback loop.
   * Updates the state of the window including the render callback function.
   */
  bool update();

  /*
   * Sets the render callback function.
   * Moves ownership of the callback function to the window.
   *
   * Parameters:
   *	callback: Render callback function.
   */
  void setRenderCallback(RenderCallback callback);

  /*
   * Wrapper for 'glfwMakeContextCurrent(m_window);'.
   */
  void makeContextCurrent();

  /*
   * Wrapper for 'glfwSwapBuffers(m_window);'.
   * Swaps the window buffers.
   */
  void swapBuffers();

  /*
   * Clears the window's buffers and colours.
   */
  void clear();

  /*
   * Sets the background colour of the window.
   *
   * Parameters:
   *	colour: Colour of the background.
	 *
	 * Preferably takes in a colour from Colour:: namespace.
	 * Example: window.setBackgroundColour(Colour::RED).
   */
  void setBackgroundColour(glm::vec4 colour);

	/*
	 * Signals the window to close by setting the 'shouldClose' flag to true.
	 */
	void close();

  /*
   * Returns whether the window should close or not.
   * Returns:
   *	True if the window should close, false otherwise.
   */
  bool shouldClose() const;

  /*
   * Gets the window as a GLFWwindow*.
   * Returns:
   *	The window as a GLFWwindow*.
   */
  GLFWwindow *getWindow() const { return m_window; }

  /*
   * Gets the width of the window.
   * Returns:
   *	The width of the window.
   */
  int getWidth() const;

  /*
   * Gets the height of the window.
   * Returns:
   *	The height of the window.
   */
  int getHeight() const;

private:
  // GLFW window instance.
  GLFWwindow *m_window = nullptr;

  // Render callback function.
  RenderCallback m_renderCallback;

  // Window width.
  int m_width = 0;

  // Window height.
  int m_height = 0;

  // Red colour component of the window.
  float m_clearR = 0.0f;

  // Green colour component of the window.
  float m_clearG = 0.0f;

  // Blue colour component of the window.
  float m_clearB = 0.0f;

  // Alpha colour component of the window.
  float m_clearA = 1.0f;
};
