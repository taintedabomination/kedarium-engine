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
}

#endif // GRAPHICS_HPP
