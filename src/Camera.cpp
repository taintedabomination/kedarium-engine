#include "Kedarium/Camera.hpp"

kdr::Camera::Camera(const CameraProps& cameraProps)
{
  this->position = cameraProps.position;
  this->orientation = glm::vec3(0.f, 0.f, -1.f);
  this->speed = cameraProps.speed;
  this->fov = cameraProps.fov;
  this->aspectRatio = cameraProps.aspectRatio;
  this->near = cameraProps.near;
  this->far = cameraProps.far;
}

const glm::vec3 kdr::Camera::getPosition() const
{
  return this->position;
}

void kdr::Camera::handleInputs(GLFWwindow* window)
{

}
