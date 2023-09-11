#include <GL/glew.h>

#include "Kedarium/Core.hpp"
#include "Kedarium/Window.hpp"
#include "Kedarium/Graphics.hpp"
#include "Kedarium/Camera.hpp"
#include "Kedarium/Color.hpp"

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

GLfloat cubeVertices[] = {
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  0.f,  1.f, // Front
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f,  1.f, // Front
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f,  1.f, // Front
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  0.f,  1.f, // Front
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f,  1.f, // Front
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f,  1.f, // Front
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  1.f,  0.f,  0.f, // Right
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  1.f,  0.f,  0.f, // Right
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  1.f,  0.f,  0.f, // Right
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  1.f,  0.f,  0.f, // Right
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  1.f,  0.f,  0.f, // Right
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  1.f,  0.f,  0.f, // Right
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  0.f, -1.f, // Back
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f, -1.f, // Back
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f, -1.f, // Back
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  0.f, -1.f, // Back
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f, -1.f, // Back
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f, -1.f, // Back
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f, -1.f,  0.f,  0.f, // Left
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,  0.f,  0.f, // Left
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, -1.f,  0.f,  0.f, // Left
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f, -1.f,  0.f,  0.f, // Left
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 1.f, -1.f,  0.f,  0.f, // Left
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,  0.f,  0.f, // Left
   0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  1.f,  0.f, // Top
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  1.f,  0.f, // Top
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  1.f,  0.f, // Top
  -0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  1.f,  0.f, // Top
   0.5f,  0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  1.f,  0.f, // Top
  -0.5f,  0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  1.f,  0.f, // Top
  -0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 1.f, 0.f,  0.f, -1.f,  0.f, // Bottom
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f, -1.f,  0.f, // Bottom
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f, -1.f,  0.f, // Bottom
   0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 0.f, 1.f,  0.f, -1.f,  0.f, // Bottom
  -0.5f, -0.5f, -0.5f, 1.f, 1.f, 1.f, 1.f, 1.f,  0.f, -1.f,  0.f, // Bottom
   0.5f, -0.5f,  0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,  0.f, -1.f,  0.f, // Bottom
};
GLuint cubeIndices[] = {
  0, 1, 2,
  3, 4, 5,
  6, 7, 8,
  9, 10, 11,
  12, 13, 14,
  15, 16, 17,
  18, 19, 20,
  21, 22, 23,
  24, 25, 26,
  27, 28, 29,
  30, 31, 32,
  33, 34, 35
};

GLfloat lightVertices[] = {
   0.25f, -0.25f,  0.25f,
  -0.25f, -0.25f,  0.25f,
   0.25f,  0.25f,  0.25f,
  -0.25f,  0.25f,  0.25f,
   0.25f,  0.25f,  0.25f,
  -0.25f, -0.25f,  0.25f,
   0.25f, -0.25f, -0.25f,
   0.25f, -0.25f,  0.25f,
   0.25f,  0.25f, -0.25f,
   0.25f,  0.25f,  0.25f,
   0.25f,  0.25f, -0.25f,
   0.25f, -0.25f,  0.25f,
  -0.25f, -0.25f, -0.25f,
   0.25f, -0.25f, -0.25f,
  -0.25f,  0.25f, -0.25f,
   0.25f,  0.25f, -0.25f,
  -0.25f,  0.25f, -0.25f,
   0.25f, -0.25f, -0.25f,
  -0.25f, -0.25f,  0.25f,
  -0.25f, -0.25f, -0.25f,
  -0.25f,  0.25f,  0.25f,
  -0.25f,  0.25f, -0.25f,
  -0.25f,  0.25f,  0.25f,
  -0.25f, -0.25f, -0.25f,
   0.25f,  0.25f,  0.25f,
  -0.25f,  0.25f,  0.25f,
   0.25f,  0.25f, -0.25f,
  -0.25f,  0.25f, -0.25f,
   0.25f,  0.25f, -0.25f,
  -0.25f,  0.25f,  0.25f,
  -0.25f, -0.25f,  0.25f,
   0.25f, -0.25f,  0.25f,
  -0.25f, -0.25f, -0.25f,
   0.25f, -0.25f, -0.25f,
  -0.25f, -0.25f, -0.25f,
   0.25f, -0.25f,  0.25f,
};
GLuint lightIndices[] = {
  0, 1, 2,
  3, 4, 5,
  6, 7, 8,
  9, 10, 11,
  12, 13, 14,
  15, 16, 17,
  18, 19, 20,
  21, 22, 23,
  24, 25, 26,
  27, 28, 29,
  30, 31, 32,
  33, 34, 35
};

class MyWindow : public kdr::Window
{
  public:
    MyWindow(const kdr::WindowProps& windowProps) : kdr::Window(windowProps)
    {
      this->cubeShader = new kdr::Shader("resources/Shaders/default.vert", "resources/Shaders/default.frag");
      this->lightShader = new kdr::Shader("resources/Shaders/light.vert", "resources/Shaders/light.frag");

      this->texture = new kdr::Texture("resources/Textures/gold.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
      this->texture->TextureUnit(*this->cubeShader, "tex0", 0);

      glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
      glm::mat4 cubeModel = glm::mat4(1.0f);
      cubeModel = glm::translate(cubeModel, cubePos);

      glm::vec3 lightPos = glm::vec3(-3.0f, 0.0f, 0.0f);
      glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.f);
      glm::mat4 lightModel = glm::mat4(1.0f);
      lightModel = glm::translate(lightModel, lightPos);

      this->CubeVAO = new kdr::VAO();
      this->CubeVBO = new kdr::VBO(cubeVertices, sizeof(cubeVertices));
      this->CubeEBO = new kdr::EBO(cubeIndices, sizeof(cubeIndices));

      this->CubeVAO->Bind();
      this->CubeVBO->Bind();
      this->CubeEBO->Bind();

      this->CubeVAO->LinkAttrib(*this->CubeVBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(0));
      this->CubeVAO->LinkAttrib(*this->CubeVBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
      this->CubeVAO->LinkAttrib(*this->CubeVBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
      this->CubeVAO->LinkAttrib(*this->CubeVBO, 3, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

      this->cubeShader->Use();

      GLuint cubeModelLocation = glGetUniformLocation(this->cubeShader->getID(), "model");
      GLuint cubeLightColorLocation = glGetUniformLocation(this->cubeShader->getID(), "lightColor");
      GLuint cubeLightPositionLocation = glGetUniformLocation(this->cubeShader->getID(), "lightPosition");

      glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, glm::value_ptr(cubeModel));
      glUniform4f(cubeLightColorLocation, lightColor.x, lightColor.y, lightColor.z, lightColor.w);
      glUniform3f(cubeLightPositionLocation, lightPos.x, lightPos.y, lightPos.z);

      this->CubeVAO->Unbind();
      this->CubeVBO->Unbind();
      this->CubeEBO->Unbind();

      this->LightVAO = new kdr::VAO();
      this->LightVBO = new kdr::VBO(lightVertices, sizeof(lightVertices));
      this->LightEBO = new kdr::EBO(lightIndices, sizeof(lightIndices));

      this->LightVAO->Bind();
      this->LightVBO->Bind();
      this->LightEBO->Bind();

      this->LightVAO->LinkAttrib(*this->LightVBO, 0, 3, GL_FLOAT, 0, (void*)(0));

      this->lightShader->Use();

      GLuint lightColorLocation = glGetUniformLocation(this->lightShader->getID(), "color");
      GLuint lightModelLocation = glGetUniformLocation(this->lightShader->getID(), "model");

      glUniformMatrix4fv(lightModelLocation, 1, GL_FALSE, glm::value_ptr(lightModel));
      glUniform4f(lightColorLocation, lightColor.x, lightColor.y, lightColor.z, lightColor.w);
      glUniform3f(lightModelLocation, lightPos.x, lightPos.y, lightPos.z);

      this->LightVAO->Unbind();
      this->LightVBO->Unbind();
      this->LightEBO->Unbind();
    };

    ~MyWindow()
    {
      this->CubeVAO->Delete();
      this->CubeVBO->Delete();
      this->CubeEBO->Delete();

      this->LightVAO->Delete();
      this->LightVBO->Delete();
      this->LightEBO->Delete();

      this->cubeShader->Delete();
      this->texture->Delete();

      delete this->cubeShader;
      delete this->lightShader;

      delete this->CubeVAO;
      delete this->CubeVBO;
      delete this->CubeEBO;

      delete this->LightVAO;
      delete this->LightVBO;
      delete this->LightEBO;

      delete this->texture;
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
      this->CubeVAO->Bind();
      glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
      
      this->lightShader->Use();
      this->bindShaderID(this->lightShader->getID());

      this->camera->useMatrix(this->lightShader->getID(), "cameraMatrix");
      this->LightVAO->Bind();
      glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    }

  private:
    kdr::Shader* cubeShader;
    kdr::Shader* lightShader;
    
    kdr::VAO* CubeVAO;
    kdr::VBO* CubeVBO;
    kdr::EBO* CubeEBO;
    
    kdr::VAO* LightVAO;
    kdr::VBO* LightVBO;
    kdr::EBO* LightEBO;

    kdr::Texture* texture;
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
