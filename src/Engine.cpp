#include "Engine.h"
#include <chrono>

void Engine::run(int width, int height, const std::string &title) {
  Window w(width, height, title);
  Input i(w);

  window = &w;
  input = &i;

  start();

  auto last = std::chrono::high_resolution_clock::now();

  while (window->update()) {
    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;

    input->update();
    update(dt);
    input->endFrame();
  }
}
