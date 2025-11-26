#pragma once

#include "Window.h"
#include <algorithm>
#include <functional>
#include <vector>

class WindowManager {
public:
  // creates a window and returns a handle
  Window *create(int w, int h, const std::string &title,
                 std::function<void(Window *)> renderCallback = nullptr) {
    Window *win = Window::createWindow(w, h, title);

    win->setRenderCallback(renderCallback);

    windows.push_back(win);

    return win;
  }

  // request window deletion
  void destroy(Window *win) { toDestroy.push_back(win); }

  bool update() {
    Window::pollGlobalEvents();

    bool anyOpen = false;
    for (auto *w : windows) {
      if (!w->shouldClose()) {
        anyOpen = true;
        w->makeContextCurrent();
        w->clear();
        w->onRender();
        w->swapBuffers();
      } else {
        toDestroy.push_back(w);
      }
    }

    if (!toDestroy.empty()) {
      for (auto *w : toDestroy) {
        auto it = std::find(windows.begin(), windows.end(), w);
        if (it != windows.end()) {
          delete *it;
          windows.erase(it);
        }
      }
      toDestroy.clear();
    }

    return anyOpen;
  }

  ~WindowManager() {
    for (auto *w : windows) {
      delete w;
    }
  }

private:
  std::vector<Window *> windows;
  std::vector<Window *> toDestroy;
};
