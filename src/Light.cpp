#include "Kedarium/Light.hpp"

kdr::Light::Light(glm::vec3 position, glm::vec4 color)
{
  this->position = position;
  this->color = color;
}

void kdr::Light::setPosition(const glm::vec3 position)
{
  this->position = position;
}

void kdr::Light::setColor(const glm::vec4 color)
{
  this->color = color;
}

void kdr::Light::setSolid(kdr::Solids::Solid* solid)
{
  this->solid = solid;
}

void kdr::Light::Use(kdr::Shader& shader)
{
  shader.Use();

  GLuint lightColorLocation = glGetUniformLocation(shader.getID(), "lightColor");
  GLuint lightModelLocation = glGetUniformLocation(shader.getID(), "lightPosition");

  glUniform4f(lightColorLocation, this->color.x, this->color.y, this->color.z, this->color.w);
  glUniform3f(lightModelLocation, this->position.x, this->position.y, this->position.z);
}

void kdr::Light::RenderSolid(kdr::Shader& shader)
{
  if (this->solid == NULL) return;

  this->solid->ApplyPosition(shader);
  this->solid->Render(shader);
}
