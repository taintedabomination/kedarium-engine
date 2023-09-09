#include "Kedarium/Camera.hpp"

kdr::Camera::Camera(const CameraProps& cameraProps)
{
  this->position = cameraProps.position;
  this->speed = cameraProps.speed;
  this->fov = cameraProps.fov;
  this->aspectRatio = cameraProps.aspectRatio;
  this->near = cameraProps.near;
  this->far = cameraProps.far;
  this->sensitivity = cameraProps.sensitivity;
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

  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  }
  if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

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
  double mouseX;
	double mouseY;
  
  glfwGetWindowSize(window, &windowWidth, &windowHeight);
  glfwGetCursorPos(window, &mouseX, &mouseY);

  float rotX = this->sensitivity * (float)(mouseY - (windowHeight / 2)) / windowHeight;
	float rotY = this->sensitivity * (float)(mouseX - (windowWidth / 2)) / windowWidth;

  glm::vec3 newOrientation = glm::rotate(
    this->orientation,
    glm::radians(-rotX),
    glm::normalize(glm::cross(
      this->orientation,
      this->up
    ))
  );
  if (abs(glm::angle(newOrientation, this->up) - glm::radians(90.0f)) <= glm::radians(85.0f))
  {
    this->orientation = newOrientation;
  }
  this->orientation = glm::rotate(this->orientation, glm::radians(-rotY), this->up);

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
