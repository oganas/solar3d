#pragma once

#include "Camera.h"
#include "Light.h"
#include "Object.h"
#include "Shader.h"
#include "Window.h"

/*
 * Renderer class.
 * Handles rendering objects.
 */
class Renderer {
public:
  /*
   * Creates a new renderer instance.
   *
   * Parameters:
   *	window: Window instance to render to.
   *	camera: Camera instance to render to.
   */
  Renderer(Window &window, Camera &camera)
      : m_window(window), m_camera(camera) {}

  /*
   * Renders an object based on the provided shader, and the object's material's
   * detail (ambient strength, specular strength, and shininess)
   *
   * Parameters:
   *	shader: Shader instance to use for rendering.
   *	objectToRender: Object to render.
   *	lights: Vector of lights to use for rendering.
   *	ambientStrength: Ambient strength of the object.
   *	specularStrength: Specular strength of the object.
   *	shininess: Shininess of the object.
   */
  void renderObject(Shader &shader, Object &objectToRender, Light light);

	/*
	 * Renders an object based on the provided shader, and the object's material's
	 * detail (ambient strength, specular strength, and shininess)
	 *
	 * Parameters:
	 *	shader: Shader instance to use for rendering.
	 *	objectToRender: Object to render.
	 */
  void renderLightSource(Shader &shader, Object &objectToRender);

private:
  /*
   * Layer of abstraction that sets up the view and projection matrices for the
   * shader.
   *
   * Parameters:
   *	shader: Shader instance to use for rendering.
   */
  void setupViewProjection(Shader &shader);

  /*
   * Layer of abstraction that sets up the lighting uniforms for the shader.
   *
   * Parameters:
   *	shader: Shader instance to use for rendering.
   *	lights: Vector of lights to use for rendering.
   *	ambientStrength: Ambient strength of the object.
   *	specularStrength: Specular strength of the object.
   *	shininess: Shininess of the object.
   */
  void setupLightingUniforms(Shader &shader, const std::vector<Light> &lights,
                             float ambientStrength, float specularStrength,
                             float shininess);

private:
  // Camera instance of this renderer instance.
  Camera &m_camera;

  // Window instance of this renderer instance.
  Window &m_window;
};
