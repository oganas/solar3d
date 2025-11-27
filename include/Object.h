#pragma once

#include <iostream>
#include <string>

#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

extern glm::vec4 defaultColour;

class Object {
public:
	std::string name;
	Mesh mesh;
	Transform transform;
	// Material material;

	Object();
  Object(std::string name);
	Object(std::string name, Mesh mesh);

	void draw(Shader& shader) const;

	// 0 to not render (hide)
	// 1 to render (show)
	void setVisibility(bool visibility);
	bool getVisibility() const;

private:
	bool m_visibility;
};
