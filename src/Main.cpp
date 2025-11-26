#include "../include/Window.h"
#include "../include/WindowManager.h"

int main() {
  WindowManager windows;

  // main window
  windows.create(1024, 768, "Main", [](Window *w) {});

  bool openedDebugOnce = false;
  Window *debugWindow = nullptr;

  while (windows.update()) {

    // spawn debug window once
    if (!openedDebugOnce) {
      openedDebugOnce = true;

      debugWindow = windows.create(500, 400, "Debug Info", [](Window *w) {
        w->setBackgroundColour(0.2f, 0.2f, 0.2f, 1.0f);
      });
    }

    static double startTime = glfwGetTime();
    if (debugWindow && glfwGetTime() - startTime > 5.0) {
      windows.destroy(debugWindow);
      debugWindow = nullptr;
    }
  }

  return 0;
}
