#include "App/AsteroidBelt.h" // Include the new header
#include "App/Planets.h"
#include "Input.h"
#include "Logger.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Object.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <glm/gtc/constants.hpp>
#include <vector>

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
Mesh planetMesh = MeshPrimitives::sphere();
Mesh saturnRingMesh = MeshPrimitives::torus(1.4, 0.4);

// Internally generated models
Object sun("sun", planetMesh);
Object moon("moon", planetMesh);
Object mercury("mercury", planetMesh);
Object venus("venus", planetMesh);
Object earth("earth", planetMesh);
Object mars("mars", planetMesh);
Object jupiter("jupiter", planetMesh);
Object saturn("saturn", planetMesh);
Object uranus("uranus", planetMesh);
Object neptune("neptune", planetMesh);
Object saturnRing("saturnRing", saturnRingMesh);

// Lights
Light light(glm::vec3(0.7f), glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f));

// Textures
Texture sunTex("sun", "planets/sun_diffuse.jpg");
Texture moonTex("moon", "planets/moon_diffuse.jpg");
Texture mercuryTex("mercury", "planets/mercury_diffuse.jpg");
Texture venusTex("venus", "planets/venus_diffuse.jpg");
Texture earthTex("earth", "planets/earth_diffuse.jpg");
Texture earthTexNormal("earthNormal", "planets/earth_normal.jpg");
Texture marsTex("mars", "planets/mars_diffuse.jpg");
Texture jupiterTex("jupiter", "planets/jupiter_diffuse.jpg");
Texture saturnTex("saturn", "planets/saturn_diffuse.jpg");
Texture uranusTex("uranus", "planets/uranus_diffuse.jpg");
Texture neptuneTex("neptune", "planets/neptune_diffuse.jpg");
Texture saturnRingTex("saturnRing", "planets/saturn_ring_diffuse2.jpg");
Texture rocket2Tex("rocket2", "RedShip_Color.png");
Texture rocket2TexNormal("rocket2Normal", "RedShip_Normal_OpenGL.png");
Texture asteroidTex("asteroid", "Asteroid1a_Color_2K.png");
Texture asteroidTexNormal("asteroidNormal", "Asteroid1a_Normal_OpenGL_2K.png");

// Textures used by AsteroidBelt (Declared as extern in AsteroidBelt.h)
Texture asteroid2Tex("asteroid2", "rock_Base_Color.png");
Texture asteroid2TexNormal("asteroid2Normal", "rock_Normal_DirectX.png");

// Skybox
Skybox space;

// Externally loaded models
Model spaceship("assets/models/use/spaceship.obj");
Model rocket("assets/models/use/rocket.obj");
Model tieFighter("assets/models/use/scene.gltf");
Model rocket2("assets/models/use/Body.fbx");
Model asteroid("assets/models/use/Asteroid_1a.fbx");

// Model used by AsteroidBelt (Declared as extern in AsteroidBelt.h)
Model asteroid2("assets/models/use/asteroid2.obj");

/*
 * Render logic.
 */
void render(Window *window) {
  // Skybox
  renderer.renderSkybox(skyboxShader, space);

  // Internally generated models
  renderer.renderObject(shader, sun, light, true);
  renderer.renderObject(shader, moon, light, false);
  renderer.renderObject(shader, mercury, light, false);
  renderer.renderObject(shader, venus, light, false);
  renderer.renderObject(shader, earth, light, false);
  renderer.renderObject(shader, mars, light, false);
  renderer.renderObject(shader, jupiter, light, false);
  renderer.renderObject(shader, saturn, light, false);
  renderer.renderObject(shader, saturnRing, light, false);
  renderer.renderObject(shader, uranus, light, false);
  renderer.renderObject(shader, neptune, light, false);

  // Externally loaded models
  renderer.renderModel(shader, spaceship, light, false);
  renderer.renderModel(shader, rocket, light, false);
  renderer.renderModel(shader, tieFighter, light, false);
  renderer.renderModel(shader, rocket2, light, false);
  renderer.renderModel(shader, asteroid, light, false);
  AsteroidBelt::renderBelt(shader, renderer);
}

/*
 * Setup / Initialisation logic.
 */
void start() {
  window.setRenderCallback(render);
  window.setBackgroundColour(Colour::BLACK);

  camera.sensitivity = 120.0f;
  camera.position = vec3(0.0f, 0.0f, 300.0f);
  camera.movementSpeed = 300.0f;
  camera.farClip = 100000000.0f;

  light.position = sun.transform.position;

  // ORIGINAL ASTEROID SETUP
  asteroid.setPosition(vec3(camera.position));
  asteroid.setScale(vec3(30.0f));
  asteroid.objects[0].material.diffuseTexture = &asteroidTex;
  asteroid.objects[0].material.normalTexture = &asteroidTexNormal;
  asteroid.objects[0].material.hasNormal = true;

  SolarSystem::setupPlanets();
  AsteroidBelt::setupBelt();

  spaceship.setPosition(vec3(300.0f, 100.0f, 500.0f));

  rocket.setPosition(vec3(0.0f, 0.0f, 300.0f));
  rocket.updateRotation(vec3(0.0f, 1.0f, 1.0f));
  rocket.setScale(vec3(0.01f));

  tieFighter.setPosition(vec3(0.0f, 0.0f, -10.0f));

  rocket2.setPosition(vec3(-10.0f, 0.0f, 300.0f));
  rocket2.setScale(vec3(0.1f));

  rocket2.objects[0].transform.rotation += vec3(0.0f, 1.6f, 0.0f);
  rocket2.objects[0].material.diffuseTexture = &rocket2Tex;
  rocket2.objects[0].material.normalTexture = &rocket2TexNormal;
  rocket2.objects[0].material.hasNormal = true;

  /*
   * Used the following to generate the faces of the cubemap:
   * https://jaxry.github.io/panorama-to-cubemap/
   */
  std::vector<std::string> faces;
  faces.push_back("space/px.png");
  faces.push_back("space/nx.png");
  faces.push_back("space/py.png");
  faces.push_back("space/ny.png");
  faces.push_back("space/pz.png");
  faces.push_back("space/nz.png");

  space = Skybox(faces);
}

/*
 * Executed every frame.
 * Frame independent logic.
 *
 * Parameters:
 *    dt: delta time
 */
void update(float dt) {
  SolarSystem::handleSolarSystemMotion(dt);

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

  if (input.isKeyPressed(Key::L)) {
    camera.position = rocket2.getPosition();
  }
  if (input.isKeyPressed(Key::K)) {
    camera.position = tieFighter.getPosition();
  }
  if (input.isKeyDown(Key::J)) {
    camera.position = spaceship.getPosition();
  }
  if (input.isKeyDown(Key::F)) {
    camera.position = saturn.transform.position;
  }

  rocket.updateRotation(vec3(0.0f, 0.0f, 0.8f) * dt);
  spaceship.updatePosition(vec3(-5.0f, 0.0f, 0.0f) * dt);
  asteroid.updateRotation(vec3(0.06f, 0.06f, 0.06f) * dt);

  AsteroidBelt::updateMotion(dt);
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
