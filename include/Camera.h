#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Direction { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;

  float yaw;
  float pitch;

  float movementSpeed;
  float sensitivity;

  float fov;
  float nearClip;
  float farClip;

  Camera(float fov = 45.0f, float nearClip = 0.1f, float farClip = 100.0f,
         glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 3.0f),
         glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f),
         float startYaw = -90.0f, float startPitch = 0.0f);

  glm::mat4 getViewMatrix() const;
  glm::mat4 getProjectionMatrix(float aspect) const;

  void move(Direction direction, float dt);
  void look(float xoffset, float yoffset, float dt);

private:
  void updateCameraVectors();
};
