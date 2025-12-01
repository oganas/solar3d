#include "Renderer.h"
#include "Light.h"
#include "Skybox.h"

// Maximum number of lights that can be used in the shader.
#define MAX_LIGHTS 4

void Renderer::setupViewProjection(Shader &shader) {
  float aspect = (float)m_window.getWidth() / (float)m_window.getHeight();

  glm::mat4 view = m_camera.getViewMatrix();
  glm::mat4 projection = m_camera.getProjectionMatrix(aspect);

  shader.setUniform("projection", projection);
  shader.setUniform("view", view);
}

void Renderer::renderObject(Shader &shader, Object &objectToRender, Light light,
                            bool isLightSource) {
  shader.bind();

  setupViewProjection(shader);

  shader.setUniform("viewPosition", m_camera.position);

  shader.setUniform("light.position", light.position);
  shader.setUniform("light.ambient", light.ambient);
  shader.setUniform("light.diffuse", light.diffuse);
  shader.setUniform("light.specular", light.specular);

  shader.setUniform("isLightSource", isLightSource);

  GLuint diffuseTextureId = 0;

  if (objectToRender.material.diffuseTexture != nullptr) {
    diffuseTextureId = objectToRender.material.diffuseTexture->getId();
  }

  if (diffuseTextureId != 0) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTextureId);
    shader.setUniform("material.textureSampler", 0);
    shader.setUniform("material.hasTexture", 1);
  } else {
    shader.setUniform("material.hasTexture", 0);
  }

  shader.setUniform("material.diffuse", objectToRender.material.diffuse);
  shader.setUniform("material.ambient", objectToRender.material.ambient);
  shader.setUniform("material.specular", objectToRender.material.specular);
  shader.setUniform("material.shininess", objectToRender.material.shininess);

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

  glBindTexture(GL_TEXTURE_2D, 0);

  shader.unbind();
}

void Renderer::renderSkybox(Shader &shader, Skybox &skybox) {
  glDepthFunc(GL_LEQUAL);

  shader.bind();

  glm::mat4 view = glm::mat4(glm::mat3(m_camera.getViewMatrix()));
  float aspect = (float)m_window.getWidth() / (float)m_window.getHeight();
  glm::mat4 projection = m_camera.getProjectionMatrix(aspect);

  shader.setUniform("view", view);
  shader.setUniform("projection", projection);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.cubemapTexture->getId());
  shader.setUniform("skybox", 0);

  skybox.draw();

  glDepthFunc(GL_LESS);

  shader.unbind();
}
