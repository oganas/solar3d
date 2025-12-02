#include "Renderer.h"
#include "Light.h"
#include "Model.h"
#include "Skybox.h"

// Maximum number of lights that can be used in the shader.
// Currently unused, but I'll leave it in for now.
#define MAX_LIGHTS 4

// Helper function for setting up the view and projection matrices.
void Renderer::setupViewProjection(Shader &shader) {
  float aspect = (float)m_window.getWidth() / (float)m_window.getHeight();

  glm::mat4 view = m_camera.getViewMatrix();
  glm::mat4 projection = m_camera.getProjectionMatrix(aspect);

  shader.setUniform("projection", projection);
  shader.setUniform("view", view);
}

/*
 * This function is responsible for rendering one object, which coulld be part
 * of a model. it binds the shader, sets up the view and projection matrices,
 * sets the lighting uniforms, sets the material uniforms, and finally draws the
 * mesh of the object.
 */
void Renderer::renderObject(Shader &shader, Object &objectToRender, Light light,
                            bool isLightSource) {
  // glUseProgram(...)
  shader.bind();

  // Set view and projection matrices
  setupViewProjection(shader);

  // Set view position
  shader.setUniform("viewPosition", m_camera.position);

  // Set lighting uniforms
  shader.setUniform("light.position", light.position);
  shader.setUniform("light.ambient", light.ambient);
  shader.setUniform("light.diffuse", light.diffuse);
  shader.setUniform("light.specular", light.specular);
  shader.setUniform("isLightSource", isLightSource);

  /*
   * If the object has a diffuse texture, set it, otherwise it would take its
   * normal diffuse colour or a default colour.
   */
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

  /*
   * If the object has a normal texture, set it, otherwise it stays with it's
   * normal normals.
   */
  if (objectToRender.material.normalTexture != nullptr &&
      objectToRender.material.hasNormal) {
    // normal map on texture unit 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,
                  objectToRender.material.normalTexture->getId());
    shader.setUniform("material.normalMap", 1);
    shader.setUniform("material.hasNormal", 1);
  } else {
    shader.setUniform("material.hasNormal", 0);
  }

  // Set material uniforms.
  shader.setUniform("material.diffuse", objectToRender.material.diffuse);
  shader.setUniform("material.ambient", objectToRender.material.ambient);
  shader.setUniform("material.specular", objectToRender.material.specular);
  shader.setUniform("material.shininess", objectToRender.material.shininess);

  // Set model matrix.
  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  // Draw the object.
  objectToRender.draw();

  glBindTexture(GL_TEXTURE_2D, 0);

  // glUseProgram(0);
  shader.unbind();
}

/*
 * Special function for rendering a skybox (a cubemap texture).
 *
 * Takes in its special skybox shader.
 */
void Renderer::renderSkybox(Shader &shader, Skybox &skybox) {
  // Makes sure the skybox is drawn even if it's the furthest thing away.
  glDepthFunc(GL_LEQUAL);

  shader.bind();

  /*
   * Took a while to understand that I can't just ignore this as I was doing at
   * first but apparently removign the translation component is key in making
   * the skybox seems infinitely far away.
   */
  glm::mat4 view = glm::mat4(glm::mat3(m_camera.getViewMatrix()));

  float aspect = (float)m_window.getWidth() / (float)m_window.getHeight();
  glm::mat4 projection = m_camera.getProjectionMatrix(aspect);

  shader.setUniform("view", view);
  shader.setUniform("projection", projection);

  /*
   * Bind the cubemap texture which would have been loaded prior to this
   * function being called.
   */
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.cubemapTexture->getId());
  shader.setUniform("skybox", 0);

  skybox.draw();

  // Revery to default depth.
  glDepthFunc(GL_LESS);

  shader.unbind();
}

/*
 * Since models are made up of objects, this function iterates over all the
 * objects that make up a model and renders them.
 *
 * I hate how inefficient this is.
 */
void Renderer::renderModel(Shader &shader, Model &model, Light light,
                           bool isLightSource) {
  for (auto &obj : model.getObjects()) {
    renderObject(shader, obj, light, isLightSource);
  }
}
