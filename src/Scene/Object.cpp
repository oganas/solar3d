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
 * Since an object's components are public, these exist solely as a gateway for
 * the model to set the position, rotation, and scale of it's objects. But in
 * reality they dont need to exist.
 */

void Object::setPosition(const glm::vec3 &position) {
  transform.position = position;
}

void Object::setRotation(const glm::vec3 &rotation) {
  transform.rotation = rotation;
}

void Object::setScale(const glm::vec3 &scale) { transform.scale = scale; }
