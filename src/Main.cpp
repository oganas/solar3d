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
Texture sunTex("sun", "planets/sun_diffuse.jpg");
Texture earthTex("earth", "planets/earth_diffuse.jpg");

// Skybox
Skybox space;

Model model("assets/models/spaceship6.glb");

/*
 * Render logic.
 * This is where rendering objects is handled.
 */
void render(Window *window) {
  renderer.renderSkybox(skyboxShader, space);
  renderer.renderObject(shader, sphere, light, false);
  renderer.renderObject(shader, sun, light, true);
  renderer.renderObject(shader, cube, light, false);

  for (auto &obj : model.objects) {
    renderer.renderObject(shader, obj, light, false);
  }
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

	// print all material properties of model
	for (auto &obj : model.objects) {
		std::cout << obj.name << std::endl;
		std::cout << "diffuse: " << obj.material.diffuse.x << " " << obj.material.diffuse.y << " " << obj.material.diffuse.z << std::endl;
		std::cout << "ambient: " << obj.material.ambient.x << " " << obj.material.ambient.y << " " << obj.material.ambient.z << std::endl;
		std::cout << "specular: " << obj.material.specular.x << " " << obj.material.specular.y << " " << obj.material.specular.z << std::endl;
		std::cout << "shininess: " << obj.material.shininess << std::endl;
	}

  /*
   * Used the following to generate the faces of the cubemap:
   * https://jaxry.github.io/panorama-to-cubemap/
   */
  std::vector<std::string> faces;
  faces.push_back("space3/px.png");
  faces.push_back("space3/nx.png");
  faces.push_back("space3/py.png");
  faces.push_back("space3/ny.png");
  faces.push_back("space3/pz.png");
  faces.push_back("space3/nz.png");

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
