#include "Kedarium/Core.hpp"

const char* ENGINE_NAME    = "Kedarium Engine";
const char* ENGINE_VERSION = "0.1";
const char* ENGINE_AUTHOR  = "taintedabomination";
const char* ENGINE_LICENSE = "GNU GPLv3";

void kdr::core::printEngineInfo()
{
  std::cout << ENGINE_NAME << " " << ENGINE_VERSION << std::endl;
  std::cout << "Created by " << ENGINE_AUTHOR << std::endl;
  std::cout << "Licensed under " << ENGINE_LICENSE << std::endl;
}

void kdr::core::printVersionInfo()
{
  std::cout << '\n';
  std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl; 
  std::cout << "GLFW:   " << glfwGetVersionString() << std::endl; 
  std::cout << "GLEW:   " << glewGetString(GLEW_VERSION) << std::endl; 
}
