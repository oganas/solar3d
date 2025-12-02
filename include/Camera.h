#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Directions for camera movement.
enum Direction { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

/*
 * Camera class.
 * Creates camera objects.
 * Handles camera movement and looking around (projection / view matrix
 * calculation).
 */
class Camera {
public:
  // Position of the camera in world space.
  glm::vec3 position;

  // Front vector of the camera in world space.
  glm::vec3 front;

  // Up vector of the camera in world space.
  glm::vec3 up;

  // Right vector of the camera in world space.
  glm::vec3 right;

  // Objective up vector of the camera in world space.
  glm::vec3 worldUp;

  // Yaw angle of the camera in radians.
  float yaw;

  // Pitch angle of the camera in radians.
  float pitch;

  // How fast the camera moves in a direction.
  float movementSpeed;

  // How fast the camera looks around.
  float sensitivity;

  // Field of view of the camera.
  float fov;

  // Near clipping plane of the camera.
  // This is the closest distance at which objects are not rendered.
  float nearClip;

  // Far clipping plane of the camera (render distance).
  // This is the farthest distance at which objects are rendered.
  float farClip;

  /*
   * Creates a new camera instance.
   *
   * Parameters:
   *   fov: Initial field of view of the camera.
   *   nearClip: Initial near clipping plane of the camera.
   *   farClip: Initial far clipping plane of the camera.
   *   startPosition: Initial position of the camera in world space.
   *   upVector: Initial up vector of the camera in world space.
   *   startYaw: Initial yaw angle of the camera in radians.
   *   startPitch: Initial pitch angle of the camera at creation.
   */
  Camera(float fov = 45.0f, float nearClip = 0.1f, float farClip = 100.0f,
         glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f),
         float startYaw = -90.0f, float startPitch = 0.0f);

  /*
   * Returns the view matrix of the camera.
   */
  glm::mat4 getViewMatrix() const;

  /*
   * Returns the projection matrix of the camera.
   *
   * Parameters:
   *	aspect: Aspect ratio of the window.
   */
  glm::mat4 getProjectionMatrix(float aspect) const;

  /*
   * Moves the camera in a direction.
   *
   * Parameters:
   *	direction: Direction to move the camera in.
   *	dt: Time delta since last frame.
   */
  void move(Direction direction, float dt);

  /*
   * Looks around the camera.
   *
   * Parameters:
   *	xoffset: Horizontal offset to look around.
   *	yoffset: Vertical offset to look around.
   *	dt: Time delta since last frame.
   */
  void look(float xoffset, float yoffset, float dt);

private:
  /*
   * Updates the camera vectors (position, front, up, right, and worldUp).
   */
  void updateCameraVectors();
};
