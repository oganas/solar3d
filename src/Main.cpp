#include "Input.h"
#include "Mesh.h"
#include "Object.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

#include <chrono>

Window w(1280, 720, "solar system");
Input i(w);

Camera camera;
Renderer r(camera);

Shader s("shaders/vs.vert", "shaders/fs.frag");

Object cube;
Object sphere;
Object sphere2;

std::vector<Light> sceneLights;

// render logic
void render(Window *window) {
	r.renderObject(*window, s, sphere, sceneLights, 0.001f, 0.01f, 1.0f);
	r.renderObject(*window, s, sphere2, sceneLights, 0.1f, 0.8f, 8.0f);
}

// init logic
void start() {
  w.setRenderCallback(render);

	w.setBackgroundColour(Colour::GRAY);

  camera.sensitivity = 85.0f;
	camera.position = vec3(0.0f, 0.0f, 15.0f);

  Mesh cubeMesh = MeshPrimitives::cube();
	Mesh sphereMesh = MeshPrimitives::sphere();

  cube = Object("cube", cubeMesh);
  cube.transform.position = vec3(0.0f, 0.0f, 0.0f);

	sphere = Object("sphere", sphereMesh);
	sphere.transform.position = vec3(-10.0f, 0.0f, 0.0f);

	sphere2 = Object("sphere2", sphereMesh);
	sphere2.transform.position = vec3(0.0f, 0.0f, 0.0f);

  sceneLights.emplace_back(glm::vec3(5.0f, 5.0f, 5.0f),
                           glm::vec3(1.0f, 1.0f, 1.0f), 0.1f,
                           0.5f);
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
	if (i.isKeyDown(Key::SPACE)) {
    camera.move(Direction::UP, dt);
  }
  if (i.isKeyDown(Key::L_SHIFT)) {
    camera.move(Direction::DOWN, dt);
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
