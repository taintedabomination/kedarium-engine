#include "Kedarium/Solids.hpp"

kdr::Solids::Solid::Solid(const glm::vec3 position)
{
  this->position = position;
  this->model = glm::translate(this->model, this->position);
}

void kdr::Solids::Solid::setPosition(const glm::vec3 position)
{
  this->position = position;
  this->model = glm::translate(glm::mat4(1.f), this->position);
}

void kdr::Solids::Solid::ApplyPosition(kdr::Shader& shader)
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

kdr::Solids::Cube::Cube(const glm::vec3 position, const float edgeLength): kdr::Solids::Solid(position)
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

  this->cubeVAO = new kdr::VAO();
  this->cubeVBO = new kdr::VBO(cubeVertices, sizeof(cubeVertices));
  this->cubeEBO = new kdr::EBO(cubeIndices, sizeof(cubeIndices));

  this->cubeVAO->Bind();
  this->cubeVBO->Bind();
  this->cubeEBO->Bind();

  this->cubeVAO->LinkAttrib(*this->cubeVBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(0));
  this->cubeVAO->LinkAttrib(*this->cubeVBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->cubeVAO->LinkAttrib(*this->cubeVBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  this->cubeVAO->LinkAttrib(*this->cubeVBO, 3, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

  this->cubeVAO->Unbind();
  this->cubeVBO->Unbind();
  this->cubeEBO->Unbind();
}

kdr::Solids::Cube::~Cube()
{
  delete this->cubeVAO;
  delete this->cubeVBO;
  delete this->cubeEBO;
}

void kdr::Solids::Cube::Render(kdr::Shader& shader)
{
  shader.Use();
  this->cubeVAO->Bind();
  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
}

kdr::Solids::ColorCube::ColorCube(const glm::vec3 position, const float edgeLength) : kdr::Solids::Solid(position), color(0.f, 0.f, 0.f, 1.f)
{
  this->position = position;
  this->color = color;

  GLfloat cubeVertices[] = {
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f),  (edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f),  (edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
    -(edgeLength / 2.f), -(edgeLength / 2.f), -(edgeLength / 2.f),
     (edgeLength / 2.f), -(edgeLength / 2.f),  (edgeLength / 2.f),
  };

  this->cubeVAO = new kdr::VAO();
  this->cubeVBO = new kdr::VBO(cubeVertices, sizeof(cubeVertices));
  this->cubeEBO = new kdr::EBO(cubeIndices, sizeof(cubeIndices));

  this->cubeVAO->Bind();
  this->cubeVBO->Bind();
  this->cubeEBO->Bind();

  this->cubeVAO->LinkAttrib(*this->cubeVBO, 0, 3, GL_FLOAT, 0, (void*)(0));

  this->cubeVAO->Unbind();
  this->cubeVBO->Unbind();
  this->cubeEBO->Unbind();
}

kdr::Solids::ColorCube::~ColorCube()
{
  delete this->cubeVAO;
  delete this->cubeVBO;
  delete this->cubeEBO;
}

void kdr::Solids::ColorCube::setColor(const kdr::Color::RGBA color)
{
  this->color = color;
}

void kdr::Solids::ColorCube::Render(kdr::Shader& shader)
{
  shader.Use();
  this->cubeVAO->Bind();

  GLuint lightColorLocation = glGetUniformLocation(shader.getID(), "color");
  glUniform4f(lightColorLocation, this->color.red, this->color.green, this->color.blue, this->color.alpha);

  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
}
