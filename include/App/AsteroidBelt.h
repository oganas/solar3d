#pragma once

#include "Render/Renderer.h"
#include "Render/Texture.h"
#include "Scene/Light.h"
#include "Scene/Model.h"
#include <vector>

// Thes objects are declared in Main.cpp

// The base model used for asteroid duplication
extern Model asteroid2;
extern Texture asteroid2Tex;
extern Texture asteroid2TexNormal;
extern Light light;

namespace AsteroidBelt {

// vector holding all individual asteroid models
extern std::vector<Model> beltModels;

// the number of asteroids in the asteroid belt
extern const int ASTEROID_COUNT;

/**
 * Initialises the asteroid belt creating all individual asteroid
 * models and setting their random positions, scales, and initial rotations
 */
void setupBelt();

/**
 * Loops through all asteroid models and calls the renderer for each one.
 * Should be called in the main render loop.
 *
 * Parameters:
 *   shader: the shader to use for rendering
 *   renderer: the renderer to use for rendering
 */
void renderBelt(Shader &shader, Renderer &renderer);

/**
 * Updates the axial rotation and orbital motion of all asteroids.
 *
 * Parameters:
 *   dt: delta time
 */
void updateMotion(float dt);

} // namespace AsteroidBelt
