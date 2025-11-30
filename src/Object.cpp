#include "Object.h"

Object::Object() {}

Object::Object(std::string name) : name(name) {}

Object::Object(std::string name, Mesh mesh) : name(name), mesh(mesh) {}

void Object::draw() const { mesh.draw(); }
