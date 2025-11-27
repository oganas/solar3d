#pragma once

#include "Input.h"
#include "Window.h"

class Engine {
public:
  Engine() = default;
  virtual ~Engine() = default;

  void run(int width = 800, int height = 600, const std::string &title = "App");

  virtual void start() {}
  virtual void update(float dt) {}

protected:
  Window *window = nullptr;
  Input *input = nullptr;
};
