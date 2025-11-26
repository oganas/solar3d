#include <iostream>

#include "../include/Window.h"

Window *window;

int main() {
  try {
		window = new Window(1024, 768, "3D Engine");
		window->setBackgroundColour(1.0f, 0.1f, 0.1f, 1.0f);

		while (!glfwWindowShouldClose(window->getWindow())) {
			window->clear();
			window->swapBuffers();
			window->pollEvents();
		}

		delete window;
  } catch (const std::exception &e) {
    std::cerr << "Fatal Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
