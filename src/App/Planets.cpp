#include "App/Planets.h"
#include <cstdlib>
#include <ctime>
#include <glm/gtc/constants.hpp>

/*
 * !!! Used AI in here to generate the orbit logic and the math and stuff
 * like that. !!!
 */

namespace SolarSystem {
static float totalSimulationTime = 0.0f;
static const float ORBITAL_SPEED_MULTIPLIER = 0.02f;
static const float AXIAL_SPEED_MULTIPLIER = 0.05f;

const float PLANET_SIZE_MULTIPLIER = 30.0f;

const float PLANITIA_ORBIT_DISTANCE = 3.0f * 50.0f;
const float PLANITIA_ORBIT_TILT_ANGLE = 15.0f;
const float PLANITIA_ELLIPTICITY = 0.3f;

const float BASE_AU_DISTANCE = 70.0f;

const float MERCURY_AU = 8.19f;
const float VENUS_AU = 15.12f;
const float EARTH_AU = 21.00f;
const float MARS_AU = 31.92f;
const float JUPITER_AU = 100.0f;
const float SATURN_AU = 150.89f;
const float URANUS_AU = 200.87f;
const float NEPTUNE_AU = 260.08f;

const float MOON_ORBIT_DISTANCE = 4.0f * 20.0f;

void updatePlanet(PlanetData &data, float dt, float time) {
  data.object.transform.rotation.z += data.axialSpeed * dt;

  float angle = time * data.orbitalSpeed;

  data.object.transform.position.x = data.orbitalRadius * cos(angle);
  data.object.transform.position.z = data.orbitalRadius * sin(angle);
}

/*
 * !!! Used AI for part going down and other parts of this file as well. !!!
 */
void handleSolarSystemMotion(float dt) {
  totalSimulationTime += dt;

  // Easy way to store and edit planets data.
  PlanetData planets[] = {
      {sun, 0.0f, 0.05f * AXIAL_SPEED_MULTIPLIER, 0.0f},
      {mercury, 1.2f * ORBITAL_SPEED_MULTIPLIER, 0.9f * AXIAL_SPEED_MULTIPLIER,
       MERCURY_AU * BASE_AU_DISTANCE},
      {venus, 0.5f * ORBITAL_SPEED_MULTIPLIER, 0.1f * AXIAL_SPEED_MULTIPLIER,
       VENUS_AU * BASE_AU_DISTANCE},
      {earth, 0.4f * ORBITAL_SPEED_MULTIPLIER, 1.3f * AXIAL_SPEED_MULTIPLIER,
       EARTH_AU * BASE_AU_DISTANCE},
      {mars, 0.8f * ORBITAL_SPEED_MULTIPLIER, 1.8f * AXIAL_SPEED_MULTIPLIER,
       MARS_AU * BASE_AU_DISTANCE},
      {jupiter, 0.4f * ORBITAL_SPEED_MULTIPLIER, 3.5f * AXIAL_SPEED_MULTIPLIER,
       JUPITER_AU * BASE_AU_DISTANCE},
      {saturn, 0.3f * ORBITAL_SPEED_MULTIPLIER, 3.0f * AXIAL_SPEED_MULTIPLIER,
       SATURN_AU * BASE_AU_DISTANCE},
      {uranus, 0.2f * ORBITAL_SPEED_MULTIPLIER, 2.5f * AXIAL_SPEED_MULTIPLIER,
       URANUS_AU * BASE_AU_DISTANCE},
      {neptune, 0.15f * ORBITAL_SPEED_MULTIPLIER, 2.2f * AXIAL_SPEED_MULTIPLIER,
       NEPTUNE_AU * BASE_AU_DISTANCE}};

  for (auto &planet : planets) {
    updatePlanet(planet, dt, totalSimulationTime);
  }

  saturnRing.transform.position = saturn.transform.position;
  saturnRing.transform.rotation.y += planets[6].axialSpeed * dt;

  float moonOrbitSpeed = 6.0f * ORBITAL_SPEED_MULTIPLIER;
  float moonAngle = totalSimulationTime * moonOrbitSpeed;

  float moonRelativeX = MOON_ORBIT_DISTANCE * cos(moonAngle);
  float moonRelativeZ = MOON_ORBIT_DISTANCE * sin(moonAngle);

  moon.transform.position.x = earth.transform.position.x + moonRelativeX;
  moon.transform.position.y = earth.transform.position.y;
  moon.transform.position.z = earth.transform.position.z + moonRelativeZ;

  moon.transform.rotation.y += 2.0f * AXIAL_SPEED_MULTIPLIER * dt;

  glm::vec3 marsPos = planets[4].object.transform.position;

  float planitiaOrbitSpeed = 4.5f * ORBITAL_SPEED_MULTIPLIER;
  float planitiaAngle = totalSimulationTime * planitiaOrbitSpeed;

  float eccentricity = PLANITIA_ELLIPTICITY;
  float baseRadius = PLANITIA_ORBIT_DISTANCE;

  float orbitalRadius = baseRadius * (1.0f - eccentricity * sin(planitiaAngle));

  float ORBIT_TILT = glm::radians(PLANITIA_ORBIT_TILT_ANGLE);

  float planeX = orbitalRadius * cos(planitiaAngle);
  float planeZ = orbitalRadius * sin(planitiaAngle);

  float newX = planeX * cos(ORBIT_TILT);
  float newY = planeX * sin(ORBIT_TILT);

  planitia.setPosition(
      glm::vec3(marsPos.x + newX, marsPos.y + newY, marsPos.z + planeZ));
}

void setupPlanets() {
  /*
   * This basically simulates randomness by fast forwarding the time of the
   * simulation and guaranteeing that it will look random because each planet
   * has its own orbital speed
   */
  srand(static_cast<unsigned int>(time(NULL)));
  totalSimulationTime = static_cast<float>(rand() % 1000);

  // Planets proportional scales to each other
  const float SUN_REL_SCALE = 10.0f * PLANET_SIZE_MULTIPLIER;
  const float MERCURY_REL_SCALE = 0.50f * PLANET_SIZE_MULTIPLIER;
  const float VENUS_REL_SCALE = 0.80f * PLANET_SIZE_MULTIPLIER;
  const float EARTH_REL_SCALE = 1.00f * PLANET_SIZE_MULTIPLIER;
  const float MARS_REL_SCALE = 0.60f * PLANET_SIZE_MULTIPLIER;
  const float JUPITER_REL_SCALE = 4.00f * PLANET_SIZE_MULTIPLIER;
  const float SATURN_REL_SCALE = 2.40f * PLANET_SIZE_MULTIPLIER;
  const float URANUS_REL_SCALE = 1.60f * PLANET_SIZE_MULTIPLIER;
  const float NEPTUNE_REL_SCALE = 1.40f * PLANET_SIZE_MULTIPLIER;
  const float MOON_REL_SCALE = 0.20f * PLANET_SIZE_MULTIPLIER;

  const float degree = -90.0f;
  const float ROTATE_90_DEGREES = degree * glm::pi<float>() / 180.0f;

  // Sun settings
  sun.transform.position = vec3(0.0f, 0.0f, 0.0f);
  sun.transform.scale = vec3(SUN_REL_SCALE);
  sun.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  sun.material.diffuseTexture = &sunTex;
  light.position = sun.transform.position;

  // Mercury settings
  mercury.transform.position = vec3(MERCURY_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  mercury.transform.scale = vec3(MERCURY_REL_SCALE);
  mercury.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  mercury.material.diffuseTexture = &mercuryTex;
  mercury.material.specular = glm::vec3(0.01f);
  mercury.material.shininess = 1.0f;

  // Venus settings
  venus.transform.position = vec3(VENUS_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  venus.transform.scale = vec3(VENUS_REL_SCALE);
  venus.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  venus.material.diffuseTexture = &venusTex;
  venus.material.specular = glm::vec3(0.01f);
  venus.material.shininess = 1.0f;

  // Earth settings
  earth.transform.position = vec3(EARTH_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  earth.transform.scale = vec3(EARTH_REL_SCALE);
  earth.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  earth.material.diffuseTexture = &earthTex;
  earth.material.normalTexture = &earthTexNormal;
  earth.material.hasNormal = true;
  earth.material.specular = glm::vec3(0.01f);
  earth.material.shininess = 1.0f;

  // Moon settings
  moon.transform.position = earth.transform.position +
                            vec3(1.0f * PLANET_SIZE_MULTIPLIER, 0.0f, 0.0f);
  moon.transform.scale = vec3(MOON_REL_SCALE);
  moon.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  moon.material.diffuseTexture = &moonTex;
  moon.material.specular = glm::vec3(0.01f);
  moon.material.shininess = 1.0f;

  // Mars settings
  mars.transform.position = vec3(MARS_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  mars.transform.scale = vec3(MARS_REL_SCALE);
  mars.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  mars.material.diffuseTexture = &marsTex;
  mars.material.specular = glm::vec3(0.01f);
  mars.material.shininess = 1.0f;

  // Jupiter settings
  jupiter.transform.position = vec3(JUPITER_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  jupiter.transform.scale = vec3(JUPITER_REL_SCALE);
  jupiter.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  jupiter.material.diffuseTexture = &jupiterTex;
  jupiter.material.specular = glm::vec3(0.01f);
  jupiter.material.shininess = 1.0f;

  // Saturn settings
  saturn.transform.position = vec3(SATURN_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  saturn.transform.scale = vec3(SATURN_REL_SCALE);
  saturn.transform.rotation = vec3(ROTATE_90_DEGREES + 0.3, 0.0f, 0.3f);
  saturn.material.diffuseTexture = &saturnTex;
  saturn.material.specular = glm::vec3(0.01f);
  saturn.material.shininess = 1.0f;

  // Saturn ring settings
  saturnRing.transform.position = saturn.transform.position;
  saturnRing.transform.scale = vec3(120.0f, 1.0f, 120.0f);
  saturnRing.transform.rotation = vec3(0.3, 0.0f, 0.0f);
  saturnRing.material.diffuseTexture = &saturnRingTex;
  saturnRing.material.ambient = glm::vec3(100.0f);

  // Uranus settings
  uranus.transform.position = vec3(URANUS_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  uranus.transform.scale = vec3(URANUS_REL_SCALE);
  uranus.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  uranus.material.diffuseTexture = &uranusTex;
  uranus.material.specular = glm::vec3(0.01f);
  uranus.material.shininess = 1.0f;

  // Neptune settings
  neptune.transform.position = vec3(NEPTUNE_AU * BASE_AU_DISTANCE, 0.0f, 0.0f);
  neptune.transform.scale = vec3(NEPTUNE_REL_SCALE);
  neptune.transform.rotation = vec3(ROTATE_90_DEGREES, 0.0f, 0.0f);
  neptune.material.diffuseTexture = &neptuneTex;
  neptune.material.specular = glm::vec3(0.01f);
  neptune.material.shininess = 1.0f;

  // No pluto because he would be too far away :(
}
} // namespace SolarSystem
