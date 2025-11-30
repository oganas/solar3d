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

  shader.setUniform("material.ambient", objectToRender.material.ambient);
  std::cout << "material.ambient: " << objectToRender.material.ambient.r << ", "
            << objectToRender.material.ambient.g << ", "
            << objectToRender.material.ambient.b << std::endl;
  shader.setUniform("material.diffuse", objectToRender.material.diffuse);
  std::cout << "material.diffuse: " << objectToRender.material.diffuse.r << ", "
            << objectToRender.material.diffuse.g << ", "
            << objectToRender.material.diffuse.b << std::endl;
  shader.setUniform("material.specular", objectToRender.material.specular);
  std::cout << "material.specular: " << objectToRender.material.specular.r
            << ", " << objectToRender.material.specular.g << ", "
            << objectToRender.material.specular.b << std::endl;
  shader.setUniform("material.shininess", objectToRender.material.shininess);
  std::cout << "material.shininess: " << objectToRender.material.shininess
            << std::endl;

  glm::mat4 model = objectToRender.transform.getMatrix();
  shader.setUniform("model", model);

  objectToRender.draw();

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
