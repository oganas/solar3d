#include "Object.h"

Object::Object() { m_visibility = true; }

Object::Object(std::string name) { m_visibility = true; }

Object::Object(std::string name, Mesh mesh) : name(name), mesh(mesh) {
  m_visibility = true;
}

void Object::draw(Shader &shader) const {
	if (getVisibility() == false) return;

  glm::mat4 model = Object::transform.getMatrix();

  shader.setUniform("model", model);

  mesh.draw();
}

void Object::setVisibility(bool visibility) { m_visibility = visibility; }

bool Object::getVisibility() const { return m_visibility; }
