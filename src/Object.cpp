#include "Object.h"
#include "Mesh.h"

Object::Object() {}

Object::Object(std::string name) : name(name), mesh(), transform(), material() {}

Object::Object(std::string name, Mesh mesh) : name(name), mesh(mesh), transform(), material() {}

Object::Object(std::string name, Mesh mesh, Material material) : name(name), mesh(mesh), transform(), material(material) {}

void Object::draw() const { mesh.draw(); }
