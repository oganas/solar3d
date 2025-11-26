#pragma once
#include "Object.h"
#include <string>
#include <memory>

using namespace glm;

class ObjectLoader {
public:
  static std::shared_ptr<Object> loadOBJObject(const std::string &filename, const vec4 &defaultColour = vec4(1.0));
};
