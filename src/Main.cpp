#include "Input.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Object.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#include <chrono>

// Core
Window window(1280, 720, "solar system");
Input input(window);
Camera camera;
Renderer renderer(window, camera);

// Shaders
Shader shader("mainShader", "shaders/main.vert", "shaders/main.frag");
Shader skyboxShader("skyboxShader", "shaders/skybox.vert",
                    "shaders/skybox.frag");

// Meshes
Mesh cubeMesh = MeshPrimitives::cube();
Mesh sphereMesh = MeshPrimitives::sphere();

// Objects
Object cube("cube", cubeMesh);
Object sphere("sphere", sphereMesh);
Object sun("sun", sphereMesh);

// Lights
Light light(glm::vec3(0.7f), glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f));

// Textures
Texture crateTex("crate", "crate.png");
Texture sunTex("sun", "use/planets/sun_diffuse.jpg");
Texture earthTex("earth", "use/planets/earth_diffuse.jpg");

// Skybox
Skybox space;

// Models
Model model("assets/models/Car.obj");

/*
 * Render logic.
 * This is where rendering objects is handled.
 */
void render(Window *window) {
  renderer.renderSkybox(skyboxShader, space);
  renderer.renderObject(shader, sphere, light, false);
  renderer.renderObject(shader, sun, light, true);
  renderer.renderObject(shader, cube, light, false);
  renderer.renderModel(shader, model, light, false);
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

  cube.transform.position = vec3(-10.0f, 0.0f, 0.0f);
  cube.material.diffuseTexture = &crateTex;

  sphere.transform.position = vec3(10.0f, 0.0f, 0.0f);
  sphere.material.diffuseTexture = &earthTex;
  sphere.material.specular = glm::vec3(0.01f);
  sphere.material.shininess = 1.0f;

  sun.transform.position = vec3(0.0f, 10.0f, 10.0f);
  sun.material.diffuseTexture = &sunTex;

  light.position = sun.transform.position;

	model.setPosition(vec3(0.0f, 0.0f, 0.0f));

  /*
   * Used the following to generate the faces of the cubemap:
   * https://jaxry.github.io/panorama-to-cubemap/
   */
  std::vector<std::string> faces;
  faces.push_back("use/space/px.png");
  faces.push_back("use/space/nx.png");
  faces.push_back("use/space/py.png");
  faces.push_back("use/space/ny.png");
  faces.push_back("use/space/pz.png");
  faces.push_back("use/space/nz.png");

  space = Skybox(faces);
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

	model.setPosition(model.getPosition() + vec3(0.0f, 0.0f, 0.1f) * dt);
}

int main() {
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
