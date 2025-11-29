#include "Renderer.h"
#include "Light.h"

// Maximum number of lights that can be used in the shader.
#define MAX_LIGHTS 4

void Renderer::setupViewProjection(Shader &shader) {
  float aspect = (float)m_window.getWidth() / (float)m_window.getHeight();

  glm::mat4 view = m_camera.getViewMatrix();
  glm::mat4 projection = m_camera.getProjectionMatrix(aspect);

  shader.setUniform("projection", projection);
  shader.setUniform("view", view);
}

void Renderer::setupLightingUniforms(Shader &shader,
                                     const std::vector<Light> &lights,
                                     float ambient, float strength,
                                     float shininess) {

  int count = glm::min((int)lights.size(), MAX_LIGHTS);
  shader.setUniform("numLights", count);

  for (int i = 0; i < count; i++) {
    const Light &light = lights[i];

    std::string prefix = "pointLights[" + std::to_string(i) + "].";

    shader.setUniform(prefix + "position", light.position);
    shader.setUniform(prefix + "colour", light.colour);
  }

  shader.setUniform("ambient", ambient);
  shader.setUniform("strength", strength);
  shader.setUniform("shininess", shininess);

  shader.setUniform("viewPosition", m_camera.position);
}

void Renderer::renderObject(Shader &shader, Object &objectToRender,
                            Light light) {
  if (objectToRender.getVisibility() == false)
    return;

  shader.bind();

  setupViewProjection(shader);

  shader.setUniform("objectColour", glm::vec3(1.0, 0.5, 0.31));
  shader.setUniform("light.colour", light.colour);
	shader.setUniform("light.position", light.position);
  shader.setUniform("viewPosition", m_camera.position);

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

  shader.unbind();
}
