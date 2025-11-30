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

void Renderer::renderObject(Shader &shader, Object &objectToRender,
                            Light light) {
  shader.bind();

  setupViewProjection(shader);

  shader.setUniform("viewPosition", m_camera.position);

  shader.setUniform("light.position", light.position);
  shader.setUniform("light.ambient", light.ambient);
  shader.setUniform("light.diffuse", light.diffuse);
  shader.setUniform("light.specular", light.specular);

  unsigned int diffuseTextureId = objectToRender.material.diffuseTextureId;

  if (diffuseTextureId != 0) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTextureId);
    shader.setUniform("material.textureSampler", 0);
    shader.setUniform("material.hasTexture", 1);
  } else {
    shader.setUniform("material.hasTexture", 0);
    shader.setUniform("material.diffuse", objectToRender.material.diffuse);
  }

  shader.setUniform("material.ambient", objectToRender.material.ambient);
  shader.setUniform("material.specular", objectToRender.material.specular);
  shader.setUniform("material.shininess", objectToRender.material.shininess);

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

  glBindTexture(GL_TEXTURE_2D, 0);

  shader.unbind();
}

void Renderer::renderLightSource(Shader &shader, Object &objectToRender) {
  shader.bind();

  setupViewProjection(shader);

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

  shader.unbind();
}
