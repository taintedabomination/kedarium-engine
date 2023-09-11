#include <GL/glew.h>

#include "Kedarium/Core.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Light.hpp"
#include "Kedarium/Solids.hpp"

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

class MyWindow : public kdr::Window
{
  public:
    MyWindow(const kdr::WindowProps& windowProps) : kdr::Window(windowProps)
    {
      this->cubeShader = new kdr::Shader("resources/Shaders/default.vert", "resources/Shaders/default.frag");

      this->texture = new kdr::Texture("resources/Textures/gold.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
      this->texture->TextureUnit(*this->cubeShader, "tex0", 0);

      this->light = new kdr::Light(
        glm::vec3(-3.f, 0.f, 0.f),
        glm::vec4(1.f, 1.f, 1.f, 1.f)
      );
      this->cube = new kdr::Solids::Cube(
        glm::vec3(0.f, 0.f, 0.f)
      );

      this->cubeShader->Use();
      this->cube->ApplyPosition(*this->cubeShader);
      this->light->Use(*this->cubeShader);
    };

    ~MyWindow()
    {
      this->cubeShader->Delete();
      this->texture->Delete();

      delete this->cubeShader;
      delete this->cube;

      delete this->texture;
      delete this->light;
    }

    void update(){}

    void render()
    {
      this->cubeShader->Use();
      this->bindShaderID(this->cubeShader->getID());

      GLuint cameraPositionLocation = glGetUniformLocation(this->cubeShader->getID(), "cameraPosition");
      glm::vec3 cameraPosition = this->camera->getPosition();

      glUniform3f(cameraPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

      this->camera->useMatrix(this->cubeShader->getID(), "cameraMatrix");
      this->texture->Bind();
      this->cube->Render(*this->cubeShader);
    }

  private:
    kdr::Shader* cubeShader;
    kdr::Solids::Cube* cube;
    kdr::Texture* texture;
    kdr::Light* light;
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
    0.05f,
    0.05f,
    0.05f,
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
