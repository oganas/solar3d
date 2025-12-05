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

// --- NEW GLOBAL CONSTANTS AND VARIABLES FOR ASTEROID BELT ---
const int ASTEROID_COUNT = 700;
std::vector<Model> asteroidBelt;
static float asteroidBeltTime = 0.0f; // Separate time tracker for belt motion
// --- END NEW GLOBALS ---

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
Model asteroid2("assets/models/use/asteroid2.obj");

// --- NEW FUNCTION: RENDER ASTEROID BELT ---
void renderAsteroidBelt() {
  for (auto &beltAsteroid : asteroidBelt) {
    renderer.renderModel(shader, beltAsteroid, light, false);
  }
}

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

  // --- RENDER THE NEW ASTEROID BELT ---
  renderAsteroidBelt();
  // ------------------------------------
}

// --- NEW FUNCTION: SETUP ASTEROID BELT ---
void setupAsteroidBelt() {
  // Define the belt's orbital zone (between Mars and Jupiter)
  // We'll place the belt from 600 units to 1300 units for a visible gap.
  const float INNER_RADIUS = 2400.0f; // Start after Mars
  const float OUTER_RADIUS = 3400.0f; // End well before Jupiter

  // Seed for random numbers
  srand(static_cast<unsigned int>(time(NULL)));

  for (int i = 0; i < ASTEROID_COUNT; ++i) {
    // 1. DUPLICATE MODEL: Create a new asteroid by copying the original,
    // which shares the underlying mesh data.
    Model newAsteroid = asteroid2;

    // 2. COPY OBJECTS AND MATERIALS: Ensure the material/textures are linked
    newAsteroid.objects = asteroid2.objects;

    // 3. TEXTURE ASSIGNMENT (Critical for duplicates)
    newAsteroid.objects[0].material.diffuseTexture = &asteroid2Tex;
    newAsteroid.objects[0].material.normalTexture = &asteroid2TexNormal;
    newAsteroid.objects[0].material.hasNormal = true;

    // 4. RANDOM POSITION (Polar Coordinates to Cartesian)

    // Get a random radius within the belt zone
    float radius =
        INNER_RADIUS +
        static_cast<float>(rand()) /
            (static_cast<float>(RAND_MAX / (OUTER_RADIUS - INNER_RADIUS)));

    // Get a random angle (0 to 360 degrees)
    float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                  2.0f * glm::pi<float>();

    // Introduce small vertical scatter (Y-axis)
    float y_scatter =
        (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) *
        300.0f;

    newAsteroid.setPosition(
        vec3(radius * cos(angle), y_scatter, radius * sin(angle)));

    // 5. RANDOM SCALE AND ROTATION

    // Random small scale (e.g., between 5.0f and 15.0f)
    float randomScale =
        0.1f + static_cast<float>(rand()) /
                   (static_cast<float>(RAND_MAX / (0.08f - 0.001f)));
    newAsteroid.setScale(vec3(randomScale));

    // Random initial rotation to make them look unique
    newAsteroid.updateRotation(vec3(static_cast<float>(rand()),
                                    static_cast<float>(rand()),
                                    static_cast<float>(rand())));

    // Add the configured asteroid to the vector
    asteroidBelt.push_back(newAsteroid);
  }
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

  SolarSystem::setupPlanets();

  light.position = sun.transform.position;

  // ORIGINAL ASTEROID SETUP
  asteroid.setPosition(vec3(camera.position));
  asteroid.setScale(vec3(30.0f));
  asteroid.objects[0].material.diffuseTexture = &asteroidTex;
  asteroid.objects[0].material.normalTexture = &asteroidTexNormal;
  asteroid.objects[0].material.hasNormal = true;

  // --- CALL THE NEW ASTEROID BELT SETUP FUNCTION ---
  setupAsteroidBelt();
  // -------------------------------------------------

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

// --- NEW FUNCTION: UPDATE ASTEROID BELT MOTION ---
void updateAsteroidBeltMotion(float dt) {
  asteroidBeltTime += dt * 0.5f; // Slower time for the belt (adjustable)

  for (auto &beltAsteroid : asteroidBelt) {
    // 1. AXIAL ROTATION (Spinning)
    // Each asteroid rotates slowly on its own axis.
    float spinSpeed = 0.01f; // Slow rotation speed
    beltAsteroid.updateRotation(vec3(spinSpeed, spinSpeed, spinSpeed) * dt);

    // 2. ORBITAL MOTION
    // Use the current position's magnitude (radius) and rotate it around the
    // origin (Sun).
    vec3 currentPos = beltAsteroid.getPosition();
    float radius = glm::length(vec2(currentPos.x, currentPos.z));

    // Calculate the current angle
    float currentAngle = atan2(currentPos.z, currentPos.x);

    // Define orbital speed (slower for larger radius)
    float orbitalSpeed =
        0.02f / (radius / 100.0f); // Slower asteroids further out

    // Update the angle
    float newAngle = currentAngle + orbitalSpeed * dt;

    // Set the new position, keeping the original y-scatter
    beltAsteroid.setPosition(
        vec3(radius * cos(newAngle), currentPos.y, radius * sin(newAngle)));
  }
}
// --- END NEW FUNCTION ---

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

  // --- CALL THE NEW ASTEROID BELT UPDATE FUNCTION ---
  updateAsteroidBeltMotion(dt);
  // --------------------------------------------------
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
