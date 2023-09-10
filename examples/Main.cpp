#include <GL/glew.h>

#include "Kedarium/Core.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Image.hpp"

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "Kedarium Engine";

const glm::vec3 CAMERA_POS         = glm::vec3(0.f, 0.f, 5.f);
const float     CAMERA_SPEED       = 4.f;
const float     CAMERA_FOV         = 45.f;
const float     CAMERA_ASPECT      = (float)(WINDOW_WIDTH) / WINDOW_HEIGHT;
const float     CAMERA_NEAR        = 0.1f;
const float     CAMERA_FAR         = 100.f;
const float     CAMERA_SENSITIVITY = 35.f;

GLfloat vertices[] = {
   0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f,
  -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 0.f, 0.f,
   0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f,
  -0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f, 0.f, 1.f,
   0.5f,  0.5f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f,
  -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 0.f, 0.f
};
GLuint indices[] = {
  0, 1, 2,
  3, 4, 5,
};

class MyWindow : public kdr::Window
{
  public:
    MyWindow(const kdr::WindowProps& windowProps) : kdr::Window(windowProps)
    {
      this->defaultShader = new kdr::Shader("resources/Shaders/default.vert", "resources/Shaders/default.frag");
      this->bindShaderID(this->defaultShader->getID());

      int textureWidth;
      int textureHeight;
      unsigned char* data;
      kdr::Image::loadFromPNG("resources/Textures/test.png", &data, textureWidth, textureHeight);

      glGenTextures(1, &this->texture);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, this->texture);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

      this->defaultShader->Use();
      GLuint tex0Location = glGetUniformLocation(this->defaultShader->getID(), "tex0");
      glUniform1i(tex0Location, 0);

      this->VAO1 = new kdr::VAO();
      this->VBO1 = new kdr::VBO(vertices, sizeof(vertices));
      this->EBO1 = new kdr::EBO(indices, sizeof(indices));

      this->VAO1->Bind();
      this->VBO1->Bind();
      this->EBO1->Bind();

      this->VAO1->LinkAttrib(*this->VBO1, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(0));
      this->VAO1->LinkAttrib(*this->VBO1, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
      this->VAO1->LinkAttrib(*this->VBO1, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

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
      glDeleteTextures(1, &this->texture);

      delete this->defaultShader;
      delete this->VAO1;
      delete this->VBO1;
      delete this->EBO1;
    }

    void update(){}

    void render()
    {
      this->defaultShader->Use();
      this->VAO1->Bind();

      glBindTexture(GL_TEXTURE_2D, this->texture);
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    kdr::Shader* defaultShader;
    kdr::VAO* VAO1;
    kdr::VBO* VBO1;
    kdr::EBO* EBO1;
    GLuint texture;
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
    CAMERA_FAR,
    CAMERA_SENSITIVITY
  );
  const kdr::Color::RGBA clearColor = kdr::Color::RGBA(
    0.0f,
    0.3f,
    0.3f,
    1.0f
  );

  MyWindow myWindow(windowProps);
  kdr::Camera myCamera(cameraProps);

  myWindow.setCamera(&myCamera);
  myWindow.setClearColor(clearColor);

  kdr::Core::printEngineInfo();
  kdr::Core::printVersionInfo();

  myWindow.loop();
  myWindow.close();

  return 0;
}
