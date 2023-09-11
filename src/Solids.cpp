#include "Kedarium/Solids.hpp"

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

kdr::Solids::Cube::Cube(glm::vec3 position)
{
  this->position = position;

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

  this->model = glm::translate(this->model, this->position);

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

void kdr::Solids::Cube::ApplyPosition(kdr::Shader& shader)
{
  shader.Use();
  GLuint cubeModelLocation = glGetUniformLocation(shader.getID(), "model");
  glUniformMatrix4fv(cubeModelLocation, 1, GL_FALSE, glm::value_ptr(this->model));
}

void kdr::Solids::Cube::Render(kdr::Shader& shader)
{
  shader.Use();
  this->cubeVAO->Bind();
  glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
}
