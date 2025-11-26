#include "Input.h"
#include "Key.h"
#include "WindowManager.h"

#include <iostream>

int main() {
  WindowManager windowManager;

  // Create two windows
  Window *mainWindow = windowManager.create(600, 400, "Main Window");
  Window *debugWindow = windowManager.create(400, 300, "Debug Window");

  // Create input objects for each window
  Input mainInput;
  Input debugInput;

  mainInput.init(mainWindow);
  debugInput.init(debugWindow);

  while (windowManager.update()) {
    // Reset per-frame states
    mainInput.resetStates();
    debugInput.resetStates();

    // Check keys in main window
    for (int k = 32; k < 350; ++k) { // GLFW key range
      if (mainInput.getKeyPress(static_cast<Key>(k))) {
        std::cout << "[Main] Key pressed: " << k << std::endl;
      }
    }

    // Check keys in debug window
    for (int k = 32; k < 350; ++k) {
      if (debugInput.getKeyPress(static_cast<Key>(k))) {
        std::cout << "[Debug] Key pressed: " << k << std::endl;
      }
    }
  }

  return 0;
}
