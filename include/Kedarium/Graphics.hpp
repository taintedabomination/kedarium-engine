#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <GL/glew.h>
#include <iostream>
#include <string>

namespace kdr
{
  class Shader
  {
    public:
      /**
       * Constructor for the Shader class.
       *
       * @param vertexPath The path to the vertex shader source file.
       * @param fragmentPath The path to the fragment shader source file.
       */
      Shader(std::string vertexPath, std::string fragmentPath);

      /**
       * Gets the ID of the shader program.
       *
       * @return The shader program ID.
       */
      const GLuint getID() const;

      /**
       * Activates the shader program for rendering.
       */
      void Use();
      /**
       * Deletes the shader program.
       */
      void Delete();

    private:
      GLuint ID;
  };

  class VBO
  {
    public:
      /**
       * @Constructor for creating a VBO.
       * 
       * @param vertices A pointer to an array of GLfloat containing vertex data.
       * @param size The size in bytes of the vertex data.
       */
      VBO(GLfloat* vertices, GLsizeiptr size);

      /**
       * Gets the ID of the VBO.
       * 
       * @return The ID of the VBO.
       */
      const GLuint getID() const;

      /**
       * Binds the VBO for use.
       */
      void Bind();
      /**
       * Unbinds the currently bound VBO.
       */
      void Unbind();
      /**
       * Deletes the VBO, releasing its resources.
       */
      void Delete();

    private:
      GLuint ID;
  };

  class EBO
  {
    public:
      /**
       * Constructor for creating an EBO.
       * 
       * @param indices A pointer to an array of GLuint containing indices.
       * @param size The size in bytes of the index data.
       */
      EBO(GLuint* indices, GLsizeiptr size);

      /**
       * Gets the ID of the EBO.
       * 
       * @return The ID of the EBO.
       */
      const GLuint getID() const;

      /**
       * Binds the EBO for use.
       */
      void Bind();
      /**
       * Unbinds the currently bound EBO.
       */
      void Unbind();
      /**
       * Deletes the EBO, releasing its resources.
       */
      void Delete();

    private:
      GLuint ID;
  };

  class VAO
  {
    public:
      /**
       * Constructor for creating a VAO.
       */
      VAO();

      /**
       * Get the ID of the VAO.
       * 
       * @return The ID of the VAO.
       */
      const GLuint getID() const;

      /**
       * Links a Vertex Buffer Object (VBO) to a vertex attribute layout in the Vertex Array Object (VAO).
       *
       * @param VBO The VBO to link.
       * @param layout The attribute layout location.
       * @param size The number of components per attribute (e.g., 3 for XYZ coordinates).
       * @param type The data type of the attribute components (e.g., GL_FLOAT for floating-point values).
       * @param stride The stride between consecutive attributes (in bytes).
       * @param offset The offset to the start of the attribute data (in bytes).
       */
      void LinkAttrib(VBO& VBO, GLuint layout, GLint size, GLenum type, GLsizei stride, const void* offset);
      /**
       * Bind the VAO for use.
       */
      void Bind();
      /**
       * Unbind the currently bound VAO.
       */
      void Unbind();
      /**
       * Delete the VAO, releasing its resources.
       */
      void Delete();

    private:
      GLuint ID;
  };
}

#endif // GRAPHICS_HPP
