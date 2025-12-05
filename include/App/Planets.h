#pragma once

#include "Render/Mesh.h"
#include "Render/Texture.h"
#include "Scene/Light.h"
#include "Scene/Model.h"
#include "Scene/Object.h"
#include <glm/glm.hpp>

using namespace glm;

// THese objects are declared in Main.cpp
extern Object sun;
extern Object moon;
extern Object mercury;
extern Object venus;
extern Object earth;
extern Object mars;
extern Object jupiter;
extern Object saturn;
extern Object uranus;
extern Object neptune;
extern Object saturnRing;

extern Light light;

extern Texture sunTex;
extern Texture moonTex;
extern Texture mercuryTex;
extern Texture venusTex;
extern Texture earthTex;
extern Texture earthTexNormal;
extern Texture marsTex;
extern Texture jupiterTex;
extern Texture saturnTex;
extern Texture uranusTex;
extern Texture neptuneTex;
extern Texture saturnRingTex;

extern Model planitia;

namespace SolarSystem {
/*
 * Initialises all the planets with all their properties like textures and
 * positions.
 */
void setupPlanets();

/*
 * Updates the axial rotation and orbital motion of all planets.
 *
 * Parameters:
 *   dt: delta time
 */
void handleSolarSystemMotion(float dt);

/*
 * Holding all the data for a planet in context of orbitig the sun.
 */
struct PlanetData {
  Object &object;
  float orbitalSpeed;
  float axialSpeed;
  float orbitalRadius;
};
} // namespace SolarSystem
