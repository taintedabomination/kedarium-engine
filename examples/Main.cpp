#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Kedarium/Core.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Camera.hpp"

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "Kedarium Engine";

const glm::vec3 CAMERA_POS    = glm::vec3(0.f, 0.f, -5.f);
const float     CAMERA_SPEED  = 10.f;
const float     CAMERA_FOV    = 45.f;
const float     CAMERA_ASPECT = (float)(WINDOW_WIDTH) / WINDOW_HEIGHT;
const float     CAMERA_NEAR   = 0.1f;
const float     CAMERA_FAR    = 100.f;

GLfloat vertices[] = {
  -0.5f,  -0.5f,  0.5f,  1.f, 0.f, 0.f,
   0.0f,  -0.5f,  0.5f,  0.f, 1.f, 0.f,
   0.5f,  -0.5f,  0.5f,  0.f, 0.f, 1.f,
  -0.5f,  -0.5f,  0.0f,  1.f, 1.f, 0.f,
   0.0f,  -0.5f,  0.0f,  0.f, 1.f, 1.f,
   0.5f,  -0.5f,  0.0f,  1.f, 0.f, 1.f,
  -0.5f,  -0.5f, -0.5f,  1.f, 0.f, 0.f,
   0.0f,  -0.5f, -0.5f,  0.f, 1.f, 0.f,
   0.5f,  -0.5f, -0.5f,  0.f, 0.f, 1.f,
  -0.25f,  0.0f,  0.25f, 1.f, 1.f, 0.f,
   0.25f,  0.0f,  0.25f, 0.f, 1.f, 1.f,
  -0.25f,  0.0f, -0.25f, 1.f, 0.f, 1.f,
   0.25f,  0.0f, -0.25f, 1.f, 0.f, 0.f,
   0.f,    0.5f,  0.f,   0.f, 1.f, 0.f,
};
GLuint indices[] = {
  1, 0, 4,
  3, 4, 0,
  2, 1, 5,
  4, 5, 1,
  4, 3, 7,
  6, 7, 3,
  5, 4, 8,
  7, 8, 4,
  0, 1, 9,
  1, 4, 9,
  4, 3, 9,
  3, 0, 9,
  1, 2, 10,
  2, 5, 10,
  5, 4, 10,
  4, 1, 10,
  3, 4, 11,
  4, 7, 11,
  7, 6, 11,
  6, 3, 11,
  4, 5, 12,
  5, 8, 12,
  8, 7, 12,
  7, 4, 12,
  10, 9, 12,
  11, 12, 9,
  9, 10, 13,
  10, 12, 13,
  12, 11, 13,
  11, 9, 13,
};

class MyWindow : public kdr::Window
{
  public:
    MyWindow(const kdr::WindowProps& windowProps) : kdr::Window(windowProps)
    {
      this->defaultShader = new kdr::Shader("resources/Shaders/default.vert", "resources/Shaders/default.frag");
      this->VAO1 = new kdr::VAO();
      this->VBO1 = new kdr::VBO(vertices, sizeof(vertices));
      this->EBO1 = new kdr::EBO(indices, sizeof(indices));

      this->VAO1->Bind();
      this->VBO1->Bind();
      this->EBO1->Bind();

      this->VAO1->LinkAttrib(*this->VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(0));
      this->VAO1->LinkAttrib(*this->VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

      this->VAO1->Unbind();
      this->VBO1->Unbind();
      this->EBO1->Unbind();
    };

    ~MyWindow()
    {
      this->VAO1->Delete();
      this->VBO1->Delete();
      this->EBO1->Delete();
      this->defaultShader->Delete();

      delete this->defaultShader;
      delete this->VAO1;
      delete this->VBO1;
      delete this->EBO1;
    }

    void setCamera(kdr::Camera& camera)
    {
      this->mainCamera = &camera;
    }

    void update()
    {
      this->mainCamera->handleInputs(this->getWindow());
      this->testRotation += this->getDeltaTime() * 100.f;
    }

    void render()
    {
      this->defaultShader->Use();
      this->VAO1->Bind();

      glm::mat4 model = glm::mat4(1.f);
      glm::mat4 view = glm::mat4(1.f);
      glm::mat4 proj = glm::mat4(1.f);

      model = glm::rotate(model, glm::radians(this->testRotation), glm::vec3(0.f, 1.f, 0.f));
      view = glm::translate(view, glm::vec3(0.f, 0.f, -5.f));
      proj = glm::perspective(
        glm::radians(CAMERA_FOV),
        (float)(WINDOW_WIDTH) / WINDOW_HEIGHT,
        CAMERA_NEAR,
        CAMERA_FAR
      );

      GLint modelLoc = glGetUniformLocation(this->defaultShader->getID(), "model");
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      GLint viewLoc = glGetUniformLocation(this->defaultShader->getID(), "view");
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
      GLint projLoc = glGetUniformLocation(this->defaultShader->getID(), "proj");
      glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    kdr::Shader* defaultShader;
    kdr::VAO* VAO1;
    kdr::VBO* VBO1;
    kdr::EBO* EBO1;

    kdr::Camera* mainCamera;
    float testRotation{0.f};
};

int main()
{
  const kdr::WindowProps windowProps = kdr::WindowProps(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE
  );
  const kdr::CameraProps cameraProps = kdr::CameraProps(
    CAMERA_POS,
    CAMERA_SPEED,
    CAMERA_FOV,
    CAMERA_ASPECT,
    CAMERA_NEAR,
    CAMERA_FAR
  );

  MyWindow myWindow(windowProps);
  kdr::Camera myCamera(cameraProps);
  myWindow.setCamera(myCamera);

  kdr::core::printEngineInfo();
  kdr::core::printVersionInfo();

  myWindow.loop();
  myWindow.close();

  return 0;
}
