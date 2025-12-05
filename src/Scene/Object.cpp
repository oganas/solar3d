#include "Scene/Object.h"
#include "Render/Mesh.h"

// Overloaded constructors for Object class.

Object::Object() {}

Object::Object(std::string name)
    : name(name), mesh(), transform(), material() {}

Object::Object(std::string name, Mesh mesh)
    : name(name), mesh(mesh), transform(), material() {}

Object::Object(std::string name, Mesh mesh, Material material)
    : name(name), mesh(mesh), transform(), material(material) {}

// Draws the object using the object's mesh's draw function.
void Object::draw() const { mesh.draw(); }

/*
 * Objects are public so these don't need to exist but makes it easier.
 */

void Object::setPosition(const glm::vec3 &position) {
  transform.position = position;
}

void Object::setRotation(const glm::vec3 &rotation) {
  transform.rotation = rotation;
}

void Object::setScale(const glm::vec3 &scale) { transform.scale = scale; }
