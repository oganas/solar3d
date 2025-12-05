#include "Core/Camera.h"
#include <cmath>

// Default camera movement speed.
const float DEFAULT_SPEED = 2.5f;

// Default camera sensitivity.
const float DEFAULT_SENSITIVITY = 75.0f;

// I pass the default values to the camera constructor.
Camera::Camera(float startFov, float startNearClip, float startFarClip,
               glm::vec3 startPosition, glm::vec3 upVector, float startYaw,
               float startPitch)
    : fov(startFov), nearClip(startNearClip), farClip(startFarClip),
      position(startPosition), worldUp(upVector), yaw(startYaw),
      pitch(startPitch), movementSpeed(DEFAULT_SPEED),
      sensitivity(DEFAULT_SENSITIVITY) {
  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const {
  return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}

void Camera::move(Direction direction, float dt) {
	// Multiply movement speed by dt to make it frame independent
  float velocity = movementSpeed * dt;

  switch (direction) {
  case FORWARD:
    position += front * velocity;
    break;
  case BACKWARD:
    position -= front * velocity;
    break;
  case LEFT:
    position -= right * velocity;
    break;
  case RIGHT:
    position += right * velocity;
    break;
  case UP:
    position += worldUp * velocity;
    break;
  case DOWN:
    position -= worldUp * velocity;
    break;
  }
}

void Camera::look(float xoffset, float yoffset, float dt) {
  glm::vec2 rotationVector = glm::vec2(xoffset, yoffset);

	// normalise
  if (glm::length(rotationVector) > 0.0f) {
    rotationVector = glm::normalize(rotationVector);
  }

  float totalRotationAmount = sensitivity * dt;

  xoffset = rotationVector.x * totalRotationAmount;
  yoffset = rotationVector.y * totalRotationAmount;

  yaw += xoffset;
  pitch += yoffset;

  // clamp pitch at 90 degrees to prevent camera flipping upside down
  pitch = glm::clamp(pitch, -89.0f, 89.0f);

  updateCameraVectors();
}
void Camera::updateCameraVectors() {
  glm::vec3 newFront;
  newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  newFront.y = sin(glm::radians(pitch));
  newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = glm::normalize(newFront);

  right = glm::normalize(glm::cross(front, worldUp));

  up = glm::normalize(glm::cross(right, front));
}
