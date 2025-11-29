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
   * Draws the object using the object's mesh's draw function.
   */
  void draw() const;

  /*
   * Sets the visibility of the object.
   *
   * Parameters:
   *	visibility: 0 to not render (hide)
   *              1 to render (show)
   */
  void setVisibility(bool visibility);

  /*
   * Gets the visibility of the object.
   * Returns:
   *	0 to not render (hidden)
   *  1 to render (shown)
   */
  bool getVisibility() const;

private:
  // Visibility of the object (hidden or shown).
  bool m_visibility;
};
