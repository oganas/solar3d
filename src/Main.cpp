#include "Engine.h"
#include "Input.h"
#include "Window.h"
#include <iostream>

class App : public Engine {
public:
  void start() override {
		loadShader("shader", "shaders/vs.vert", "shaders/fs.frag");
    setWindowBackgroundColour(0.2f, 0.3f, 0.4f, 1.0f);

  }

  void update(float dt) override {
    if (isKeyDown(Key::SPACE)) {
      std::cout << "Jump!\n";
			setWindowBackgroundColour(0.0f, 0.0f, 0.0f, 1.0f);
    }
  }
};
int main() {
  App simulation;
  simulation.run(1280, 720, "solar system");
}
