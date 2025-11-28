#include "Renderer.h"

void Renderer::setupViewProjection(Window &window, Shader &shader) {
  float aspect = (float)window.getWidth() / (float)window.getHeight();

  glm::mat4 view = camera.getViewMatrix();
  glm::mat4 projection = camera.getProjectionMatrix(aspect);

  shader.setUniform("projection", projection);
  shader.setUniform("view", view);
}

void Renderer::renderObject(Window &window, Shader &shader,
                            Object &objectToRender) {
	if (objectToRender.getVisibility() == false) return;

  shader.bind();

  setupViewProjection(window, shader);

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

  shader.unbind();
}
