#pragma once

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "Shader.h"
#include "Window.h"

class Renderer {
private:
  Camera &m_camera;
	Window &m_window;

public:
  Renderer(Window &w, Camera &c) : m_window(w), m_camera(c) {}

  void renderObject(Shader &shader, Object &objectToRender,
                    const std::vector<Light> &lights, float ambientStrength,
                    float specularStrength, float shininess);

private:
  void setupViewProjection(Shader &shader);
  void setupLightingUniforms(Shader &shader, const std::vector<Light> &lights,
                             float ambientStrength, float specularStrength,
                             float shininess);
};
