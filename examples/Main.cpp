#include <GL/glew.h>
#include <vector>

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

      this->texture1 = new kdr::Texture("resources/Textures/tiles.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
      this->texture1->TextureUnit(*this->cubeShader, "tex0", 0);

      this->light = new kdr::Light(
        kdr::XYZ(0.f, 3.f, 0.f),
        kdr::Color::RGBA(1.f, 1.f, 1.f, 1.f)
      );
      this->lightCube = new kdr::Solids::ColorCube(
        kdr::XYZ(0.f, 3.f, 0.f),
        0.25f
      );

      for (int z = 0; z < 32; z++)
      {
        for (int x = 0; x < 32; x++)
        {
          this->cubes.push_back(new kdr::Solids::Cube(
            kdr::XYZ((float)(x), sin(x / 2.f) * cos(z / 2.f), (float)(z)),
            1.f
          ));
        }
      }
    };

    ~MyWindow()
    {
      this->cubeShader->Delete();
      this->colorCubeShader->Delete();

      this->texture1->Delete();

      delete this->light;
      delete this->lightCube;

      delete this->cubeShader;
      delete this->colorCubeShader;

      delete this->texture1;
    }

    void update(){
      this->light->setPosition(kdr::XYZ(
        ((float)sin(this->getTime()) + 1.f) * 16.f,
        5.f,
        ((float)sin(this->getTime()) + 1.f) * 16.f
      ));
    }

    void render()
    {
      this->bindShaderID(this->cubeShader->getID());

      GLuint cameraPositionLocation = glGetUniformLocation(this->cubeShader->getID(), "cameraPosition");
      glm::vec3 cameraPosition = this->camera->getPosition();

      glUniform3f(cameraPositionLocation, cameraPosition.x, cameraPosition.y, cameraPosition.z);

      this->lightCube->setColor(this->light->getColor());
      this->light->Use(*this->cubeShader);
      this->light->setSolid(this->lightCube);

      this->texture1->Bind();

      this->colorCubeShader->Use();
      this->camera->useMatrix(this->colorCubeShader->getID(), "cameraMatrix");

      this->light->RenderSolid(*this->colorCubeShader);

      this->cubeShader->Use();
      this->camera->useMatrix(this->cubeShader->getID(), "cameraMatrix");
      this->texture1->Bind();

      for (kdr::Solids::Cube* cube : this->cubes)
      {
        cube->Render(*this->cubeShader);
      }
    }

  private:
    kdr::Shader* cubeShader;
    kdr::Shader* colorCubeShader;

    kdr::Light* light;
    kdr::Solids::ColorCube* lightCube;

    std::vector<kdr::Solids::Cube*> cubes;

    kdr::Texture* texture1;
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
