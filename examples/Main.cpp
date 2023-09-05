#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Graphics.hpp"

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "Kedarium Engine";

GLfloat vertices[] = {
  -0.5f,  -0.5f, 0.f, 1.f, 0.f, 0.f,
   0.0f,  -0.5f, 0.f, 0.f, 1.f, 0.f,
   0.5f,  -0.5f, 0.f, 0.f, 0.f, 1.f,
  -0.25f,  0.0f, 0.f, 1.f, 1.f, 0.f,
   0.25f,  0.0f, 0.f, 0.f, 1.f, 1.f,
   0.0f,   0.5f, 0.f, 1.f, 0.f, 1.f,
};
GLuint indices[] = {
  0, 1, 3,
  1, 2, 4,
  3, 4, 5,
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

      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(GLfloat)), (void*)0);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(GLfloat)), (void*)(3 * sizeof(GLfloat)));
      glEnableVertexAttribArray(1);

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

    void update()
    {

    }

    void render()
    {
      this->defaultShader->Use();
      this->VAO1->Bind();
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    kdr::Shader* defaultShader;
    kdr::VAO* VAO1;
    kdr::VBO* VBO1;
    kdr::EBO* EBO1;
};

int main()
{
  const kdr::WindowProps windowProps = kdr::WindowProps(
    800,
    600,
    "Kedarium Engine"
  );
  MyWindow myWindow(windowProps);

  kdr::core::printEngineInfo();
  kdr::core::printVersionInfo();

  myWindow.loop();
  myWindow.close();

  return 0;
}
