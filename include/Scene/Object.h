#pragma once

#include <iostream>
#include <string>

#include "Component/Material.h"
#include "Render/Mesh.h"
#include "Render/Shader.h"
#include "Component/Transform.h"

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

	/*
   * Sets the position of the object.
   *
   * Parameters:
   *	position: new poosition of the object.
   */
	void setPosition(const glm::vec3 &position);

	/*
   * Sets the rotation of the object.
   *
   * Parameters:
   *	rotation: new rotation of the object.
   */
	void setRotation(const glm::vec3 &rotation);

	/*
   * Sets the scale of the object.
   *
   * Parameters:
   *	scale: new scale of the object.
   */
	void setScale(const glm::vec3 &scale);

private:

};
