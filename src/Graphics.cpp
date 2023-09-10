#include "Kedarium/Graphics.hpp"
#include "Kedarium/File.hpp"
#include "Kedarium/Image.hpp"

kdr::Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
  std::string vertexShaderSource = kdr::File::getContents("resources/Shaders/default.vert");
  std::string fragmentShaderSource = kdr::File::getContents("resources/Shaders/default.frag");

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
  glBindBuffer(GL_ARRAY_BUFFER, 0);
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
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

kdr::VAO::VAO()
{
  glGenVertexArrays(1, &this->ID);
}

const GLuint kdr::VAO::getID() const
{
  return this->ID;
}

void kdr::VAO::LinkAttrib(kdr::VBO& VBO, GLuint layout, GLint size, GLenum type, GLsizei stride, const void* offset)
{
  VBO.Bind();
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

void kdr::VAO::Bind()
{
  glBindVertexArray(this->ID);
}

void kdr::VAO::Unbind()
{
  glBindVertexArray(0);
}

void kdr::VAO::Delete()
{
  glDeleteVertexArrays(1, &this->ID);
}

kdr::Texture::Texture(std::string path, GLenum type, GLenum slot, GLenum format, GLenum pixelType)
{
  this->type = type;

  int textureWidth;
  int textureHeight;
  unsigned char* data;
  kdr::Image::loadFromPNG(path, &data, textureWidth, textureHeight);

  glGenTextures(1, &this->ID);
  glActiveTexture(slot);
  glBindTexture(this->type, this->ID);

  glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(this->type, 0, GL_RGBA, textureWidth, textureHeight, 0, format, pixelType, data);
}

void kdr::Texture::TextureUnit(kdr::Shader& shader, std::string uniform, GLuint unit)
{
  shader.Use();
  GLuint tex0Location = glGetUniformLocation(shader.getID(), uniform.c_str());
  glUniform1i(tex0Location, unit);
}

void kdr::Texture::Bind()
{
  glBindTexture(this->type, this->ID);
}

void kdr::Texture::Unbind()
{
  glBindTexture(this->type, 0);  
}

void kdr::Texture::Delete()
{
  glDeleteTextures(1, &this->ID);
}
