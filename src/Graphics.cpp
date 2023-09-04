#include "Kedarium/Graphics.hpp"
#include "Kedarium/File.hpp"

kdr::Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
  std::string vertexShaderSource = kdr::file::getContents("resources/Shaders/default.vert");
  std::string fragmentShaderSource = kdr::file::getContents("resources/Shaders/default.frag");

  const char *vertexCStringSource = vertexShaderSource.c_str();
  const char *fragmentCStringSource = fragmentShaderSource.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexCStringSource, NULL);
  glShaderSource(fragmentShader, 1, &fragmentCStringSource, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  char infoLog[512];
  int success;

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  this->ID = glCreateProgram();

  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);

  glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
    std::cerr << "Failed to link the shader program!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

const GLuint kdr::Shader::getID() const
{
  return this->ID;
}

void kdr::Shader::Use()
{
  glUseProgram(this->ID);
}

void kdr::Shader::Delete()
{
  glDeleteProgram(this->ID);
}

kdr::VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

const GLuint kdr::VBO::getID() const
{
  return this->ID;
}

void kdr::VBO::Bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void kdr::VBO::Unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void kdr::VBO::Delete()
{
  glDeleteBuffers(1, &this->ID);
}

kdr::EBO::EBO(GLuint* indices, GLsizeiptr size)
{
  glGenBuffers(1, &this->ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

const GLuint kdr::EBO::getID() const
{
  return this->ID;
}

void kdr::EBO::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void kdr::EBO::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void kdr::EBO::Delete()
{
  glDeleteBuffers(1, &this->ID);
}
