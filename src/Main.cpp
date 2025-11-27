#include "Engine.h"
#include "Input.h"
#include "Window.h"
#include <iostream>

class App : public Engine {
public:
  void start() override {
    window->setBackgroundColour(0.2f, 0.3f, 0.4f, 1.0f);

  }

  void update(float dt) override {
    if (input->isKeyDown(Key::SPACE)) {
      std::cout << "Jump!\n";
			window->setBackgroundColour(0.0f, 0.0f, 0.0f, 1.0f);
    }
  }
};
int main() {
  App simulation;
  simulation.run(1280, 720, "solar system");
}
