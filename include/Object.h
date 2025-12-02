#pragma once

#include <iostream>
#include <string>

#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

/*
 * Object class.
 * Creates objects.
 * Contains the mesh, transform, and material of an object.
 */
class Object {
public:
  // Name of the object.
  std::string name;

  // Mesh component of the object.
  Mesh mesh;

  // Transform component of the object.
  Transform transform;

  // Material component of the object.
  Material material;

  /*
   * Creates a new object instance.
   * This is the default constructor.
   */
  Object();

  /*
   * Creates a new object instance.
   *
   * Parameters:
   *	name: Name of the object.
   */
  Object(std::string name);

	/*
	 * Creates a new object instance.
	 *
	 * Parameters:
	 *	name: Name of the object.
	 *	mesh: Mesh of the object.
	 */
	Object(std::string name, Mesh mesh);

  /*
   * Creates a new object instance.
   *
   * Parameters:
   *	name: Name of the object.
   *	mesh: Mesh of the object.
   */
  Object(std::string name, Mesh mesh, Material material);

  /*
   * Draws the object using the object's mesh's draw function.
   */
  void draw() const;

	void setPosition(const glm::vec3 &position);
	void setRotation(const glm::vec3 &rotation);
	void setScale(const glm::vec3 &scale);

private:

};
