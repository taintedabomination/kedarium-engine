#include "Kedarium/Light.hpp"

kdr::Light::Light(const kdr::XYZ position, const kdr::Color::RGBA color) : color(1.f, 1.f, 1.f, 1.f)
{
  this->position = position;
  this->color = color;
}

const kdr::Color::RGBA kdr::Light::getColor() const
{
  return this->color;
}

void kdr::Light::setPosition(const kdr::XYZ position)
{
  this->position = position;
}

void kdr::Light::setColor(const kdr::Color::RGBA color)
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

  glUniform4f(lightColorLocation, this->color.red, this->color.green, this->color.blue, this->color.alpha);
  glUniform3f(lightModelLocation, this->position.x, this->position.y, this->position.z);
}

void kdr::Light::RenderSolid(kdr::Shader& shader)
{
  if (this->solid == NULL) return;

  this->solid->setPosition(this->position);
  this->solid->Render(shader);
}
