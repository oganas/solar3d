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
Mesh saturnRingMesh = MeshPrimitives::torus(1.3, 0.3);

// Objects
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

// Skybox
Skybox space;

// Models
Model spaceship("assets/models/use/spaceship.obj");
Model rocket("assets/models/use/rocket.obj");
Model tieFighter("assets/models/use/scene.gltf");
Model rocket2("assets/models/use/Body.fbx");

/*
 * Render logic.
 * This is where rendering objects is handled.
 */
void render(Window *window) {
  renderer.renderSkybox(skyboxShader, space);

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

  renderer.renderModel(shader, spaceship, light, false);
  renderer.renderModel(shader, rocket, light, false);
  renderer.renderModel(shader, tieFighter, light, false);
  renderer.renderModel(shader, rocket2, light, false);
}

void setupPlanets() {
  const float BASE_AU_DISTANCE = 50.0f;

  const float PLANET_SIZE_MULTIPLIER = 20.0f;

  const float MERCURY_AU = 2.73f;   // 0.39 * 7
  const float VENUS_AU = 5.04f;     // 0.72 * 7
  const float EARTH_AU = 7.00f;     // 1.00 * 7
  const float MARS_AU = 10.64f;     // 1.52 * 7
  const float JUPITER_AU = 36.40f;  // 5.20 * 7
  const float SATURN_AU = 67.06f;   // 9.58 * 7
  const float URANUS_AU = 134.61f;  // 19.23 * 7
  const float NEPTUNE_AU = 210.70f; // 30.10 * 7

  const float SUN_REL_SCALE = 5.0f * PLANET_SIZE_MULTIPLIER;
  const float MERCURY_REL_SCALE = 0.25f * PLANET_SIZE_MULTIPLIER;
  const float VENUS_REL_SCALE = 0.4f * PLANET_SIZE_MULTIPLIER;
  const float EARTH_REL_SCALE = 0.5f * PLANET_SIZE_MULTIPLIER;
  const float MARS_REL_SCALE = 0.3f * PLANET_SIZE_MULTIPLIER;
  const float JUPITER_REL_SCALE = 1.5f * PLANET_SIZE_MULTIPLIER;
  const float SATURN_REL_SCALE = 1.2f * PLANET_SIZE_MULTIPLIER;
  const float URANUS_REL_SCALE = 0.8f * PLANET_SIZE_MULTIPLIER;
  const float NEPTUNE_REL_SCALE = 0.7f * PLANET_SIZE_MULTIPLIER;
  const float MOON_REL_SCALE = 0.1f * PLANET_SIZE_MULTIPLIER;

  const float degree = -90.0f;
  const float ROTATE_90_DEGREES = degree * glm::pi<float>() / 180.0f;

  sun.transform.position = vec3(0.0f, 0.0f, 0.0f);
  sun.transform.scale = vec3(SUN_REL_SCALE);
  sun.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  sun.material.diffuseTexture = &sunTex;
  light.position = sun.transform.position;

  mercury.transform.position = vec3(MERCURY_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  mercury.transform.scale = vec3(MERCURY_REL_SCALE);
  mercury.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  mercury.material.diffuseTexture = &mercuryTex;
  mercury.material.specular = glm::vec3(0.01f);
  mercury.material.shininess = 1.0f;

  venus.transform.position = vec3(VENUS_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  venus.transform.scale = vec3(VENUS_REL_SCALE);
  venus.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  venus.material.diffuseTexture = &venusTex;
  venus.material.specular = glm::vec3(0.01f);
  venus.material.shininess = 1.0f;

  earth.transform.position = vec3(EARTH_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  earth.transform.scale = vec3(EARTH_REL_SCALE);
  earth.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  earth.material.diffuseTexture = &earthTex;
  earth.material.normalTexture = &earthTexNormal;
  earth.material.hasNormal = true;
  earth.material.specular = glm::vec3(0.01f);
  earth.material.shininess = 1.0f;

  moon.transform.position = earth.transform.position +
                            vec3(1.0f * PLANET_SIZE_MULTIPLIER, 0.0f, 0.0f);
  moon.transform.scale = vec3(MOON_REL_SCALE);
  moon.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  moon.material.diffuseTexture = &moonTex;
  moon.material.specular = glm::vec3(0.01f);
  moon.material.shininess = 1.0f;

  mars.transform.position = vec3(MARS_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  mars.transform.scale = vec3(MARS_REL_SCALE);
  mars.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  mars.material.diffuseTexture = &marsTex;
  mars.material.specular = glm::vec3(0.01f);
  mars.material.shininess = 1.0f;

  jupiter.transform.position = vec3(JUPITER_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  jupiter.transform.scale = vec3(JUPITER_REL_SCALE);
  jupiter.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  jupiter.material.diffuseTexture = &jupiterTex;
  jupiter.material.specular = glm::vec3(0.01f);
  jupiter.material.shininess = 1.0f;

  saturn.transform.position = vec3(SATURN_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  saturn.transform.scale = vec3(SATURN_REL_SCALE);
  saturn.transform.rotation = vec3(ROTATE_90_DEGREES + 0.3, 0.0f, 0.3f);
  saturn.material.diffuseTexture = &saturnTex;
  saturn.material.specular = glm::vec3(0.01f);
  saturn.material.shininess = 1.0f;

  saturnRing.transform.position = saturn.transform.position;
  saturnRing.transform.scale = vec3(35.0f, 1.0f, 35.0f);
  saturnRing.transform.rotation = vec3(0.3, 0.0f, 0.0f);
  saturnRing.material.diffuseTexture = &saturnRingTex;
  saturnRing.material.specular = glm::vec3(0.01f);
  saturnRing.material.shininess = 1.0f;

  uranus.transform.position = vec3(URANUS_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  uranus.transform.scale = vec3(URANUS_REL_SCALE);
  uranus.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  uranus.material.diffuseTexture = &uranusTex;
  uranus.material.specular = glm::vec3(0.01f);
  uranus.material.shininess = 1.0f;

  neptune.transform.position = vec3(NEPTUNE_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  neptune.transform.scale = vec3(NEPTUNE_REL_SCALE);
  neptune.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  neptune.material.diffuseTexture = &neptuneTex;
  neptune.material.specular = glm::vec3(0.01f);
  neptune.material.shininess = 1.0f;
}

/*
 * Initialisation logic.
 * This is where the window is set up and the camera is initialised.
 * + anything else that needs to be initialised.
 */
void start() {
  window.setRenderCallback(render);
  window.setBackgroundColour(Colour::BLACK);

  camera.sensitivity = 120.0f;
  camera.position = vec3(0.0f, 0.0f, 300.0f);
  camera.position = saturnRing.transform.position;
  camera.movementSpeed = 200.0f;
  camera.farClip = 100000000.0f;

  setupPlanets();

  light.position = sun.transform.position;

  spaceship.setPosition(vec3(0.0f, 0.0f, 0.0f));

  rocket.setPosition(vec3(0.0f, 0.0f, 10.0f));
  rocket.setScale(vec3(0.01f));

  tieFighter.setPosition(vec3(0.0f, 0.0f, -10.0f));

  rocket2.setPosition(vec3(0.0f, 0.0f, -30.0f));
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

  if (input.isKeyDown(Key::L)) {
    saturnRing.transform.rotation =
        saturnRing.transform.rotation + vec3(0.0f, 0.0f, 0.5f) * dt;
    saturn.transform.rotation =
        saturn.transform.rotation + vec3(0.0f, 0.0f, 0.5f) * dt;
  }
  if (input.isKeyDown(Key::K)) {
    saturnRing.transform.rotation =
        saturnRing.transform.rotation - vec3(0.0f, 0.5f, 0.0f) * dt;
    saturn.transform.rotation =
        saturn.transform.rotation - vec3(0.0f, 0.5f, 0.0f) * dt;
  }
  if (input.isKeyDown(Key::J)) {
    saturnRing.transform.rotation =
        saturnRing.transform.rotation + vec3(0.5f, 0.0f, 0.0f) * dt;
    saturn.transform.rotation =
        saturn.transform.rotation + vec3(0.5f, 0.0f, 0.0f) * dt;
  }
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
