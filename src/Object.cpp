#include "Object.h"
#include "Mesh.h"

Object::Object() {}

Object::Object(std::string name)
    : name(name), mesh(), transform(), material() {}

Object::Object(std::string name, Mesh mesh)
    : name(name), mesh(mesh), transform(), material() {}

Object::Object(std::string name, Mesh mesh, Material material)
    : name(name), mesh(mesh), transform(), material(material) {}

void Object::draw() const { mesh.draw(); }

void Object::setPosition(const glm::vec3 &position) {
  transform.position = position;
}

void Object::setRotation(const glm::vec3 &rotation) {
  transform.rotation = rotation;
}

void Object::setScale(const glm::vec3 &scale) { transform.scale = scale; }
