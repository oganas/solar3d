#include "Engine.h"
#include "Input.h"
#include "Mesh.h"
#include "Object.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

#include <chrono>
#include <iostream>

using namespace glm;

/*
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
*/

Window w(1280, 720, "solar system");
Input i(w);

Camera camera;
Renderer r(camera);

Shader s("shaders/vs.vert", "shaders/fs.frag");
Object cube;

// render logic
void render(Window *window) { r.renderObject(*window, s, cube); }

// init logic
void start() {
  w.setRenderCallback(render);

	camera.sensitivity = 75.0f;

  Mesh cubeMesh = MeshPrimitives::cube();

  cube = Object("cube", cubeMesh);
  cube.transform.position = vec3(0.0f, 0.0f, 0.0f);
}

// program logic
void update(float dt) {
  if (i.isKeyPressed(Key::Z)) {
    cube.setVisibility(false);
  }
	if (i.isKeyPressed(Key::X)) {
    cube.setVisibility(true);
	}
	if (i.isKeyDown(Key::W)) {
    camera.move(Direction::FORWARD, dt);
  }
	if (i.isKeyDown(Key::S)) {
    camera.move(Direction::BACKWARD, dt);
  }
	if (i.isKeyDown(Key::A)) {
    camera.move(Direction::LEFT, dt);
  }
	if (i.isKeyDown(Key::D)) {
    camera.move(Direction::RIGHT, dt);
  }
	if (i.isKeyDown(Key::ARROW_KEY_LEFT)) {
		camera.look(-1.0f, 0.0f, dt);
	}
	if (i.isKeyDown(Key::ARROW_KEY_RIGHT)) {
		camera.look(1.0f, 0.0f, dt);
	}
	if (i.isKeyDown(Key::ARROW_KEY_UP)) {
		camera.look(0.0f, 1.0f, dt);
	} 
	if (i.isKeyDown(Key::ARROW_KEY_DOWN)) {
		camera.look(0.0f, -1.0f, dt);
	}
	
  cube.transform.rotation += vec3(0.1f, 0.1f, 0.1f) * dt;
}

int main() {
  start();

  auto last = std::chrono::high_resolution_clock::now();

  while (w.update()) {
    i.update();

    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;

    update(dt);

    i.endFrame();
  }
}
