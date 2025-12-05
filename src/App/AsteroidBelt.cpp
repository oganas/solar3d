#include "App/AsteroidBelt.h"
#include "Misc/Logger.h"
#include "Render/Renderer.h"
#include "Render/Shader.h"

#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

/*
 * Asteroid belt logic.
 *
 * !!! Used AI to generate some of the math and asteroid spread logic. It was
 * not used as generated, it was adapted into the already existing code. !!!
 */
namespace AsteroidBelt {
std::vector<Model> beltModels;
const int ASTEROID_COUNT = 200;
static float beltTime = 0.0f;

// Where the asteroids start generating
const float INNER_RADIUS = 3600.0f;

// Where the asteroids stop generating
const float OUTER_RADIUS = 5200.0f;

void setupBelt() {
  // Seed for random numbers
  srand(static_cast<unsigned int>(time(NULL)));

  // 29/11 TODO: Segfault here
  // 04/12 Make sure the base model has loaded its objects before trying to copy
  if (asteroid2.objects.empty()) {
    Logger::log("AsteroidBelt", "model (asteroid2) objects are empty.");
    return;
  }

  for (int i = 0; i < ASTEROID_COUNT; ++i) {
    // Copy original asteroid
    Model newAsteroid = asteroid2;

    // Days to figure out that you have to do this to force it to copy
    newAsteroid.objects = asteroid2.objects;

    // Assign textures to the new aasteroid
    newAsteroid.objects[0].material.diffuseTexture = &asteroid2Tex;
    newAsteroid.objects[0].material.normalTexture = &asteroid2TexNormal;
    newAsteroid.objects[0].material.hasNormal = true;

    // Set it's radius to random
    float radius =
        INNER_RADIUS +
        static_cast<float>(rand()) /
            (static_cast<float>(RAND_MAX / (OUTER_RADIUS - INNER_RADIUS)));

    // Set it's angle to random
    float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                  2.0f * glm::pi<float>();

    // Small vertical scatter (Y-axis)
    float y_scatter =
        (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) *
        600.0f;

    newAsteroid.setPosition(
        glm::vec3(radius * cos(angle), y_scatter, radius * sin(angle)));

    // Random scale ranges
    float minScale = 0.2f;
    float maxScale = 0.4f;
    float randomScale =
        minScale + static_cast<float>(rand()) /
                       (static_cast<float>(RAND_MAX / (maxScale - minScale)));

    newAsteroid.setScale(glm::vec3(randomScale));

    // Random initial rotation
    newAsteroid.updateRotation(glm::vec3(static_cast<float>(rand()),
                                         static_cast<float>(rand()),
                                         static_cast<float>(rand())));

    beltModels.push_back(newAsteroid);
  }
}

void renderBelt(Shader &shader, Renderer &renderer) {
  for (auto &beltAsteroid : beltModels) {
    renderer.renderModel(shader, beltAsteroid, light, false);
  }
}

void updateMotion(float dt) {
  beltTime += dt * 0.5f;

  for (auto &beltAsteroid : beltModels) {
    // Rotation around axis
    float spinSpeed = 0.1f;
    beltAsteroid.updateRotation(glm::vec3(spinSpeed, spinSpeed, spinSpeed) *
                                dt);

    // Rotation around orbit
    glm::vec3 currentPos = beltAsteroid.getPosition();
    float radius = glm::length(glm::vec2(currentPos.x, currentPos.z));

    float currentAngle = atan2(currentPos.z, currentPos.x);

    // The ones on the outside are slower
    float orbitalSpeed = 0.2f / (radius / 100.0f);

    float newAngle = currentAngle + orbitalSpeed * dt;

    beltAsteroid.setPosition(glm::vec3(radius * cos(newAngle), currentPos.y,
                                       radius * sin(newAngle)));
  }
}

} // namespace AsteroidBelt
