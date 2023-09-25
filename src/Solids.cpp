#include "Kedarium/Solids.hpp"

kdr::Solids::Solid::Solid(const kdr::XYZ position)
{
  this->position = position;
  this->model = glm::translate(this->model, glm::vec3(
    this->position.x,
    this->position.y,
    this->position.z
  ));
}

void kdr::Solids::Solid::setPosition(const kdr::XYZ position)
{
  this->position = position;
  this->model = glm::translate(glm::mat4(1.f), glm::vec3(
    position.x,
    position.y,
    position.z
  ));
}

const kdr::XYZ kdr::Solids::Solid::getPosition() const
{
  return this->position;
}

void kdr::Solids::Solid::_applyPosition(kdr::Shader& shader)
{
  shader.Use();
  GLuint cubeModelLocation = glGetUniformLocation(shader.getID(), "model");
  glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, glm::value_ptr(this->model));
}

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
GLuint colorCubeIndices[] = {
  1, 0, 5,
  4, 5, 0,
  3, 1, 7,
  5, 7, 1,
  2, 3, 6,
  7, 6, 3,
  0, 2, 4,
  6, 4, 2,
  5, 4, 7,
  6, 7, 4,
  2, 3, 0,
  1, 0, 3,
};
GLuint planeIndices[] = {
  0, 1, 2,
  3, 4, 5,
};

kdr::Solids::Cube::Cube(const kdr::XYZ position, const float edgeLength): kdr::Solids::Solid(position)
{
  this->position = position;
  GLfloat cubeVertices[] = {
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  0.f,  1.f, // Front
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f,  1.f, // Front
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f,  1.f, // Front
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  0.f,  1.f, // Front
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f,  1.f, // Front
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f,  1.f, // Front
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f,  1.f,  0.f,  0.f, // Right
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  1.f,  0.f,  0.f, // Right
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  1.f,  0.f,  0.f, // Right
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f,  1.f,  0.f,  0.f, // Right
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  1.f,  0.f,  0.f, // Right
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  1.f,  0.f,  0.f, // Right
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  0.f, -1.f, // Back
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f, -1.f, // Back
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f, -1.f, // Back
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  0.f, -1.f, // Back
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  0.f, -1.f, // Back
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  0.f, -1.f, // Back
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, -1.f,  0.f,  0.f, // Left
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,  0.f,  0.f, // Left
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, -1.f,  0.f,  0.f, // Left
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, -1.f,  0.f,  0.f, // Left
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, -1.f,  0.f,  0.f, // Left
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, -1.f,  0.f,  0.f, // Left
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f,  0.f,  1.f,  0.f, // Top
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  1.f,  0.f, // Top
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  1.f,  0.f, // Top
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f,  0.f,  1.f,  0.f, // Top
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f,  1.f,  0.f, // Top
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f,  1.f,  0.f, // Top
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f,  0.f, -1.f,  0.f, // Bottom
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f, -1.f,  0.f, // Bottom
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f, -1.f,  0.f, // Bottom
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f,  0.f, -1.f,  0.f, // Bottom
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f,  0.f, -1.f,  0.f, // Bottom
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f,  0.f, -1.f,  0.f, // Bottom
  };

  this->VAO = new kdr::VAO();
  this->VBO = new kdr::VBO(cubeVertices, sizeof(cubeVertices));
  this->EBO = new kdr::EBO(cubeIndices, sizeof(cubeIndices));

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttrib(*this->VBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(0));
  this->VAO->LinkAttrib(*this->VBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttrib(*this->VBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  this->VAO->LinkAttrib(*this->VBO, 3, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

kdr::Solids::Cube::~Cube()
{
  delete this->VAO;
  delete this->VBO;
  delete this->EBO;
}

void kdr::Solids::Cube::Render(kdr::Shader& shader)
{
  shader.Use();

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->_applyPosition(shader);
  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
}

kdr::Solids::ColorCube::ColorCube(const kdr::XYZ position, const float edgeLength) : kdr::Solids::Solid(position), color(0.f, 0.f, 0.f, 1.f)
{
  this->position = position;
  this->color = color;

  GLfloat colorCubeVertices[] = {
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
  };

  this->VAO = new kdr::VAO();
  this->VBO = new kdr::VBO(colorCubeVertices, sizeof(colorCubeVertices));
  this->EBO = new kdr::EBO(colorCubeIndices, sizeof(colorCubeIndices));

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttrib(*this->VBO, 0, 3, GL_FLOAT, 0, (void*)(0));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

kdr::Solids::ColorCube::~ColorCube()
{
  delete this->VAO;
  delete this->VBO;
  delete this->EBO;
}

void kdr::Solids::ColorCube::setColor(const kdr::Color::RGBA color)
{
  this->color = color;
}

void kdr::Solids::ColorCube::Render(kdr::Shader& shader)
{
  shader.Use();

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->_applyPosition(shader);

  GLuint lightColorLocation = glGetUniformLocation(shader.getID(), "color");
  glUniform4f(lightColorLocation, this->color.red, this->color.green, this->color.blue, this->color.alpha);

  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
}

kdr::Solids::Plane::Plane(const kdr::XYZ position, const float edgeLength): kdr::Solids::Solid(position)
{
  this->position = position;
  GLfloat planeVertices[] = {
     (edgeLength / 2.f), 0.f,  (edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0,
    -(edgeLength / 2.f), 0.f,  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0,
     (edgeLength / 2.f), 0.f, -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0,
    -(edgeLength / 2.f), 0.f, -(edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0,
     (edgeLength / 2.f), 0.f, -(edgeLength / 2.f), 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0,
    -(edgeLength / 2.f), 0.f,  (edgeLength / 2.f), 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0,
  };

  this->VAO = new kdr::VAO();
  this->VBO = new kdr::VBO(planeVertices, sizeof(planeVertices));
  this->EBO = new kdr::EBO(planeIndices, sizeof(planeIndices));

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttrib(*this->VBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(0));
  this->VAO->LinkAttrib(*this->VBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttrib(*this->VBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  this->VAO->LinkAttrib(*this->VBO, 3, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

kdr::Solids::Plane::~Plane()
{
  delete this->VAO;
  delete this->VBO;
  delete this->EBO;
}

void kdr::Solids::Plane::Render(kdr::Shader& shader)
{
  shader.Use();

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->_applyPosition(shader);
  glDrawElements(GL_TRIANGLES, sizeof(planeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
}
