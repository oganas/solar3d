#include "Renderer.h"
#include "Light.h"

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
                                     float ambientStrength,
                                     float specularStrength,
                                     float shininess) {

  int count = glm::min((int)lights.size(), MAX_LIGHTS);
  shader.setUniform("numLights", count);

  for (int i = 0; i < count; i++) {
    const Light &light = lights[i];

    std::string prefix = "pointLights[" + std::to_string(i) + "].";

    shader.setUniform(prefix + "position", light.position);
    shader.setUniform(prefix + "colour", light.colour);
  }

  shader.setUniform("ambientStrength", ambientStrength);
  shader.setUniform("specularStrength", specularStrength);
  shader.setUniform("shininess", shininess);

  shader.setUniform("viewPosition", m_camera.position);
}

void Renderer::renderObject(Shader &shader,
                            Object &objectToRender,
                            const std::vector<Light> &lights,
                            float ambientStrength,
                            float specularStrength,
                            float shininess) {

  if (objectToRender.getVisibility() == false)
    return;

  shader.bind();

  setupViewProjection(shader);

  // Pass all three material properties to the lighting setup function
  setupLightingUniforms(shader, lights, ambientStrength, specularStrength,
                        shininess);

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

  shader.unbind();
}
