#include "App/AsteroidBelt.h"
#include "Misc/Logger.h" // Assuming you might use this for debugging
#include "Render/Renderer.h"
#include "Render/Shader.h"

#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// --- NAMESPACE MEMBER DEFINITIONS (must match extern declarations in .h) ---
namespace AsteroidBelt {

std::vector<Model> beltModels;
const int ASTEROID_COUNT = 600;
static float beltTime = 0.0f;

// Define the orbital zone radii (using the values from your last main.cpp)
const float INNER_RADIUS = 3600.0f; // Start after Mars
const float OUTER_RADIUS = 5200.0f; // End well before Jupiter

void setupBelt() {
  // Seed for random numbers
  srand(static_cast<unsigned int>(time(NULL)));

  // Ensure the base model has loaded its objects before attempting to copy
  if (asteroid2.objects.empty()) {
    Logger::log("AsteroidBelt", "model 'asteroid2' objects are empty.");
    return;
  }

  for (int i = 0; i < ASTEROID_COUNT; ++i) {
    // 1. DUPLICATE MODEL: Create a new asteroid instance by copying the base
    // model.
    Model newAsteroid = asteroid2;

    // 2. COPY OBJECTS: Ensure the internal objects (containing mesh/material
    // pointers) are copied from the base model where textures were correctly
    // assigned.
    newAsteroid.objects = asteroid2.objects;

    // 3. TEXTURE ASSIGNMENT (Safety check and linking)
    // Even though 'objects' were copied, explicitly re-link the textures to be
    // safe.
    newAsteroid.objects[0].material.diffuseTexture = &asteroid2Tex;
    newAsteroid.objects[0].material.normalTexture = &asteroid2TexNormal;
    newAsteroid.objects[0].material.hasNormal = true;

    // 4. RANDOM POSITION

    // Random radius
    float radius =
        INNER_RADIUS +
        static_cast<float>(rand()) /
            (static_cast<float>(RAND_MAX / (OUTER_RADIUS - INNER_RADIUS)));

    // Random angle (0 to 360 degrees)
    float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) *
                  2.0f * glm::pi<float>();

    // Small vertical scatter (Y-axis)
    float y_scatter =
        (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5f) *
        600.0f;

    newAsteroid.setPosition(
        glm::vec3(radius * cos(angle), y_scatter, radius * sin(angle)));

    // 5. RANDOM SCALE AND ROTATION

    // Random scale (0.001f to 0.08f based on your last code)
    float minScale = 0.2f;
    float maxScale = 0.4f;
    float randomScale =
        minScale + static_cast<float>(rand()) /
                       (static_cast<float>(RAND_MAX / (maxScale - minScale)));

    // Note: The original code used 0.1f + rand_range_calc, which is
    // non-standard. I'm simplifying the random range generation here to ensure
    // scales are small.
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
    // Note: The light variable is extern and assumed to be available
    renderer.renderModel(shader, beltAsteroid, light, false);
  }
}

void updateMotion(float dt) {
  beltTime += dt * 0.5f;

  for (auto &beltAsteroid : beltModels) {
    // 1. AXIAL ROTATION (Spinning)
    float spinSpeed = 0.1f; // Slightly faster spin for better visual effect
    beltAsteroid.updateRotation(glm::vec3(spinSpeed, spinSpeed, spinSpeed) *
                                dt);

    // 2. ORBITAL MOTION
    glm::vec3 currentPos = beltAsteroid.getPosition();
    float radius = glm::length(glm::vec2(currentPos.x, currentPos.z));

    float currentAngle = atan2(currentPos.z, currentPos.x);

    // Orbital speed: slower for larger radius, scaled for visibility
    // Divide by 100.0f to keep the orbital speed multiplier sensible
    float orbitalSpeed = 0.2f / (radius / 100.0f);

    float newAngle = currentAngle + orbitalSpeed * dt;

    // Update position
    beltAsteroid.setPosition(glm::vec3(radius * cos(newAngle), currentPos.y,
                                       radius * sin(newAngle)));
  }
}

} // namespace AsteroidBelt
