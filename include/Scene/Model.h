#pragma once

#include "Scene/Object.h"
#include "Render/Texture.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include <iostream>
#include <stb_image.h>
#include <string>
#include <vector>

/*
 * Model class.
 *
 * A model is a collection of objects. An object is a single unit or a wrapper
 * around a mesh. It can be externally loaded from a file or internally created.
 * This is very inefficient but oh well.
 *
 * Used the following for help and inspiration:
 * https://learnopengl.com/Model-Loading/Assimp
 * https://www.youtube.com/watch?v=sP_kiODC25Q
 * https://www.mbsoftworks.sk/tutorials/opengl3/20-assimp-model-loading/
 * https://www.ogldev.org/www/tutorial22/tutorial22.html
 */
class Model {
public:
  void appendModel(const std::string &path);

	// Vector of sub objects that make up the model.
  std::vector<Object> objects;

  /*
   * Creates a new model instance.
   *
   * Parameters:
   *	path: Path to the model file.
   */
  Model(const std::string &path);

  /*
   * Sets the position of the model.
   *
   * Parameters:
   *	position: Position of the model.
   */
  void setPosition(const glm::vec3 &position);

	/*
	 * Updates the position of the model.
	 *
	 * Parameters:
	 *	position: Position of the model.
	 */
	void updatePosition(const glm::vec3 &position);

  /*
   * Sets the rotation of the model.
   *
   * Parameters:
   *	rotation: Rotation of the model.
   */
  void setRotation(const glm::vec3 &rotation);

	/*
	 * Updates the rotation of the model.
	 *
	 * Parameters:
	 *	rotation: Rotation of the model.
	 */
	void updateRotation(const glm::vec3 &rotation);

  /*
   * Sets the scale of the model.
   *
   * Parameters:
   *	scale: Scale of the model.
   */
  void setScale(const glm::vec3 &scale);

	/*
	 * Updates the scale of the model.
	 *
	 * Parameters:
	 *	scale: Scale of the model.
	 */
	void updateScale(const glm::vec3 &scale);

  /*
   * Gets the position of the model.
   *
   * Returns:
   *	The position of the model.
   */
  glm::vec3 getPosition() const;

  /*
   * Gets the rotation of the model.
   *
   * Returns:
   *	The rotation of the model.
   */
  glm::vec3 getRotation() const;

  /*
   * Gets the scale of the model.
   *
   * Returns:
   *	The scale of the model.
   */
  glm::vec3 getScale() const;

  /*
   * Gets the objects of the model.
   *
   * Returns:
   *	The objects of the model.
   */
  std::vector<Object> getObjects() const;

private:
  /*
   * Loads a model.
   *
   * Parameters:
   *	path: Path to the model file.
   */
  void loadModel(const std::string &path);

  /*
   * Processes a node in the assimp scene.
   * Used to walk through the scene and process each node and its children.
   *
   * Parameters:
   *	node: Node to process.
   *	scene: Scene to process.
   */
  void processNode(aiNode *node, const aiScene *scene);

  /*
   * Processes assimp mesh.
   *
   * Parameters:
   *	mesh: Mesh to process.
   *	scene: Scene to process.
   */
  Object processMesh(aiMesh *mesh, const aiScene *scene);
};
