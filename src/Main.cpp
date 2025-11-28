#include "Input.h"
#include "Mesh.h"
#include "Object.h"
#include "Renderer.h"
#include "Shader.h"
#include "Window.h"

#include <chrono>

Window window(1280, 720, "solar system");
Input input(window);
Camera camera;
Renderer renderer(window, camera);

Shader shader("shaders/vs.vert", "shaders/fs.frag");

Object cube;
Object sphere;
Object sphere2;

std::vector<Light> lights;

/*
 * Render logic.
 * This is where rendering objects is handled.
 */
void render(Window *window) {
  renderer.renderObject(shader, sphere, lights, 0.001f, 0.01f, 1.0f);
  renderer.renderObject(shader, sphere2, lights, 0.1f, 0.8f, 8.0f);
  renderer.renderObject(shader, cube, lights, 0.001f, 0.8f, 0.2f);
}

/*
 * Initialisation logic.
 * This is where the window is set up and the camera is initialised.
 * + anything else that needs to be initialised.
 */
void start() {
  window.setRenderCallback(render);

  window.setBackgroundColour(Colour::GRAY);

  camera.sensitivity = 85.0f;
  camera.position = vec3(0.0f, 0.0f, 15.0f);

  Mesh cubeMesh = MeshPrimitives::cube();
  Mesh sphereMesh = MeshPrimitives::sphere();

  cube = Object("cube", cubeMesh);
  cube.transform.position = vec3(10.0f, 0.0f, 0.0f);

  sphere = Object("sphere", sphereMesh);
  sphere.transform.position = vec3(-10.0f, 0.0f, 0.0f);

  sphere2 = Object("sphere2", sphereMesh);
  sphere2.transform.position = vec3(0.0f, 0.0f, 0.0f);

  lights.emplace_back(glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

/*
 * Program logic.
 * This is where the main logic is handled.
 * + anything else that needs to be updated every frame.
 */
void update(float dt) {
  if (input.isKeyPressed(Key::Z)) {
    cube.setVisibility(false);
  }
  if (input.isKeyPressed(Key::X)) {
    cube.setVisibility(true);
  }
  if (input.isKeyDown(Key::W)) {
    camera.move(Direction::FORWARD, dt);
  }
  if (input.isKeyDown(Key::S)) {
    camera.move(Direction::BACKWARD, dt);
  }
  if (input.isKeyDown(Key::A)) {
    camera.move(Direction::LEFT, dt);
  }
  if (input.isKeyDown(Key::D)) {
    camera.move(Direction::RIGHT, dt);
  }
  if (input.isKeyDown(Key::SPACE)) {
    camera.move(Direction::UP, dt);
  }
  if (input.isKeyDown(Key::L_SHIFT)) {
    camera.move(Direction::DOWN, dt);
  }
  if (input.isKeyDown(Key::ARROW_KEY_LEFT)) {
    camera.look(-1.0f, 0.0f, dt);
  }
  if (input.isKeyDown(Key::ARROW_KEY_RIGHT)) {
    camera.look(1.0f, 0.0f, dt);
  }
  if (input.isKeyDown(Key::ARROW_KEY_UP)) {
    camera.look(0.0f, 1.0f, dt);
  }
  if (input.isKeyDown(Key::ARROW_KEY_DOWN)) {
    camera.look(0.0f, -1.0f, dt);
  }

  cube.transform.rotation += vec3(0.1f, 0.1f, 0.1f) * dt;
}

int main() {
	// initialise whatever needs to be initialised
  start();

	// last frame time
  auto last = std::chrono::high_resolution_clock::now();

  while (window.update()) {
    input.update();

    auto now = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(now - last).count();
    last = now;

    update(dt);

    input.endFrame();
  }
}
