#include "Input.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#include <chrono>

Window window(1280, 720, "solar system");
Input input(window);
Camera camera;
Renderer renderer(window, camera);

Shader shader("mainShader", "shaders/vs.vert", "shaders/fs.frag");
Shader sunShader("sunShader", "shaders/sun.vert", "shaders/sun.frag");

Mesh cubeMesh = MeshPrimitives::cube();
Mesh sphereMesh = MeshPrimitives::sphere();

Object cube("cube", cubeMesh);
Object sphere("sphere", sphereMesh);
Object sun("sun", sphereMesh);

Light light(glm::vec3(0.7f), glm::vec3(0.3f), glm::vec3(1.0f), glm::vec3(1.0f));

/*
 * Render logic.
 * This is where rendering objects is handled.
 */
void render(Window *window) {
  renderer.renderObject(shader, sphere, light);
  renderer.renderLightSource(sunShader, sun);
  renderer.renderObject(shader, cube, light);
}

/*
 * Initialisation logic.
 * This is where the window is set up and the camera is initialised.
 * + anything else that needs to be initialised.
 */
void start() {
  window.setRenderCallback(render);

  window.setBackgroundColour(Colour::BLACK);

  camera.sensitivity = 100.0f;
  camera.position = vec3(0.0f, 0.0f, 30.0f);
	camera.movementSpeed = 5.0f;

  unsigned int textureId = Texture::loadTexture("crate.png");

  cube.transform.position = vec3(-10.0f, 0.0f, 0.0f);
	cube.material.diffuseTextureId = textureId;

  sphere.transform.position = vec3(10.0f, 0.0f, 0.0f);
  sphere.material = MaterialPresets::MATERIAL_CHROME;

  sun.transform.position = vec3(0.0f, 10.0f, 10.0f);

  light.position = sun.transform.position;
}

/*
 * Program logic.
 * This is where the main logic is handled.
 * + anything else that needs to be updated every frame.
 */
void update(float dt) {
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
