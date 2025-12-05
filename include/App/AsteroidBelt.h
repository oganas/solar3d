#pragma once

#include "Scene/Light.h"
#include "Scene/Model.h"
#include "Render/Renderer.h"
#include "Render/Texture.h"
#include <vector>

// Forward declarations for external objects used by the belt.
// These objects are defined in main.cpp and are needed to initialize the belt.
extern Model asteroid2; // The base model used for duplication
extern Texture asteroid2Tex;
extern Texture asteroid2TexNormal;
extern Light light; // The light source needed for rendering

namespace AsteroidBelt {

// The vector holding all individual asteroid models
extern std::vector<Model> beltModels;

// The number of asteroids in the belt
extern const int ASTEROID_COUNT;

/**
 * @brief Initializes the asteroid belt, creating all individual asteroid
 * models, setting their random positions, scales, and initial rotations.
 */
void setupBelt();

/**
 * @brief Loops through all asteroid models and calls the renderer for each one.
 * Must be called in the main render loop.
 */
void renderBelt(Shader &shader, Renderer &renderer);

/**
 * @brief Updates the axial rotation and orbital motion of all asteroids.
 * @param dt Delta time.
 */
void updateMotion(float dt);

} // namespace AsteroidBelt
