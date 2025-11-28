#include "Object.h"

Object::Object() { m_visibility = true; }

Object::Object(std::string name) { m_visibility = true; }

Object::Object(std::string name, Mesh mesh) : name(name), mesh(mesh) {
  m_visibility = true;
}

void Object::draw() const {
  if (getVisibility() == false)
    return;

  mesh.draw();
}

void Object::setVisibility(bool visibility) { m_visibility = visibility; }

bool Object::getVisibility() const { return m_visibility; }
