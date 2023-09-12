#include <GL/glew.h>

#include "Kedarium/Core.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Color.hpp"
#include "Kedarium/Light.hpp"
#include "Kedarium/Solids.hpp"

const unsigned int WINDOW_WIDTH  = 1280;
const unsigned int WINDOW_HEIGHT = 720;
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
      this->colorCubeShader = new kdr::Shader("resources/Shaders/colored.vert", "resources/Shaders/colored.frag");

      this->texture1 = new kdr::Texture("resources/Textures/gold.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
      this->texture1->TextureUnit(*this->cubeShader, "tex0", 0);
      this->texture2 = new kdr::Texture("resources/Textures/diamond.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
      this->texture2->TextureUnit(*this->cubeShader, "tex0", 0);
      this->texture3 = new kdr::Texture("resources/Textures/soulsand.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
      this->texture3->TextureUnit(*this->cubeShader, "tex0", 0);

      this->light = new kdr::Light(
        glm::vec3(0.f, 3.f, 0.f),
        kdr::Color::RGBA(1.f, 1.f, 1.f, 1.f)
      );
      this->lightCube = new kdr::Solids::ColorCube(
        glm::vec3(0.f, 3.f, 0.f),
        0.25f
      );
      this->cube1 = new kdr::Solids::Cube(
        glm::vec3(-2.f, 0.f, 0.f),
        1.f
      );
      this->cube2 = new kdr::Solids::Cube(
        glm::vec3(0.f, 0.f, 0.f),
        1.f
      );
      this->cube3 = new kdr::Solids::Cube(
        glm::vec3(2.f, 0.f, 0.f),
        1.f
      );
    };

    ~MyWindow()
    {
      this->cubeShader->Delete();
      this->colorCubeShader->Delete();

      this->texture1->Delete();
      this->texture2->Delete();
      this->texture3->Delete();

      delete this->light;
      delete this->lightCube;

      delete this->cubeShader;
      delete this->colorCubeShader;

      delete this->cube1;
      delete this->cube2;
      delete this->cube3;

      delete this->texture1;
      delete this->texture2;
      delete this->texture3;
    }

    void update(){}

    void render()
    {
      this->bindShaderID(this->cubeShader->getID());

      GLuint cameraPositionLocation = glGetUniformLocation(this->cubeShader->getID(), "cameraPosition");
      glm::vec3 cameraPosition = this->camera->getPosition();

      glUniform3f(cameraPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

      this->camera->useMatrix(this->cubeShader->getID(), "cameraMatrix");
      this->light->setPosition(glm::vec3(
        sin(this->getTime() * 5.f) * 2.5,
        3.f,
        0.f
      ));
      this->light->setColor(kdr::Color::RGBA(
        (sin(this->getTime() * 3.f) + 1.f) / 2.f,
        (sin(this->getTime() * 2.f) + 1.f) / 2.f,
        (sin(this->getTime() * 1.f) + 1.f) / 2.f,
        1.f
      ));
      this->lightCube->setColor(kdr::Color::RGBA(
        (sin(this->getTime() * 3.f) + 1.f) / 2.f,
        (sin(this->getTime() * 2.f) + 1.f) / 2.f,
        (sin(this->getTime() * 1.f) + 1.f) / 2.f,
        1.f
      ));
      this->lightCube->setPosition(glm::vec3(
        sin(this->getTime() * 5.f) * 2.f,
        3.f,
        0.f
      ));
      this->light->Use(*this->cubeShader);
      this->light->setSolid(this->lightCube);

      this->texture1->Unbind();
      this->texture2->Unbind();
      this->texture3->Unbind();

      this->colorCubeShader->Use();
      this->camera->useMatrix(this->colorCubeShader->getID(), "cameraMatrix");

      this->light->RenderSolid(*this->colorCubeShader);

      this->cubeShader->Use();
      this->camera->useMatrix(this->cubeShader->getID(), "cameraMatrix");

      this->texture1->Bind();
      this->cube1->ApplyPosition(*this->cubeShader);
      this->cube1->Render(*this->cubeShader);
      this->texture2->Bind();
      this->cube2->ApplyPosition(*this->cubeShader);
      this->cube2->Render(*this->cubeShader);
      this->texture3->Bind();
      this->cube3->ApplyPosition(*this->cubeShader);
      this->cube3->Render(*this->cubeShader);
    }

  private:
    kdr::Shader* cubeShader;
    kdr::Shader* colorCubeShader;

    kdr::Light* light;
    kdr::Solids::ColorCube* lightCube;

    kdr::Solids::Cube* cube1;
    kdr::Solids::Cube* cube2;
    kdr::Solids::Cube* cube3;

    kdr::Texture* texture1;
    kdr::Texture* texture2;
    kdr::Texture* texture3;
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
