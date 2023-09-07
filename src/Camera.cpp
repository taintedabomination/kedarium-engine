#include "Kedarium/Camera.hpp"

kdr::Camera::Camera(const CameraProps& cameraProps)
{
  this->position = cameraProps.position;
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

void kdr::Camera::handleInputs(GLFWwindow* window, const float deltaTime)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    this->mouseLocked = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
  {
    this->mouseLocked = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  if (!mouseLocked) return;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    this->position += this->speed * deltaTime * this->orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    this->position += -this->speed * deltaTime * glm::cross(this->orientation, this->up);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    this->position += -this->speed * deltaTime * this->orientation;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    this->position += this->speed * deltaTime * glm::cross(this->orientation, this->up);
  }
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
  {
    this->position += -this->speed * deltaTime * this->up;
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    this->position += this->speed * deltaTime * this->up;
  }

  int windowWidth;
  int windowHeight;
  glfwGetWindowSize(window, &windowWidth, &windowHeight);
  glfwSetCursorPos(window, (double)windowWidth / 2, (double)windowHeight / 2);
}

void kdr::Camera::updateMatrices(GLuint programId, std::string uniform)
{
  glm::mat4 view = glm::mat4(1.f);
  glm::mat4 proj = glm::mat4(1.f);

  view = glm::lookAt(this->position, this->position + this->orientation, this->up);
  proj = glm::perspective(
    glm::radians(this->fov),
    this->aspectRatio,
    this->near,
    this->far
  );

  GLint uniformLoc = glGetUniformLocation(programId, uniform.c_str());
  glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(proj * view));
}
