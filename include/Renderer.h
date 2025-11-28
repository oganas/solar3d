#pragma once

#include "Camera.h"
#include "Object.h"
#include "Shader.h"
#include "Window.h"

class Renderer {
private:
  Camera &camera;

public:
  Renderer(Camera &c) : camera(c) {}

  void renderObject(Window &window, Shader &shader, Object &objectToRender);

private:
  void setupViewProjection(Window &window, Shader &shader);
};
