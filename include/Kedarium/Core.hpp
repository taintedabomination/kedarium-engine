#ifndef CORE_HPP
#define CORE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace kdr
{
  namespace core
  {
    /**
     * Prints information about the engine.
     */
    void printEngineInfo();
    /**
     * Prints version information about OpenGL, GLFW, and GLEW.
     */
    void printVersionInfo();
  }
}

#endif // CORE_HPP
