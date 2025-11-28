#pragma once

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "Shader.h"
#include "Window.h"

class Renderer {
private:
  Camera &camera;

public:
  Renderer(Camera &c) : camera(c) {}

  void renderObject(Window &window, Shader &shader, Object &objectToRender,
                    const std::vector<Light> &lights, float ambientStrength,
                    float specularStrength, float shininess);

private:
  void setupViewProjection(Window &window, Shader &shader);
  void setupLightingUniforms(Shader &shader, const std::vector<Light> &lights,
                             float ambientStrength, float specularStrength,
                             float shininess);
};
