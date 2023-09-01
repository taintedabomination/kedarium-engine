#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/File.hpp"

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "Kedarium Engine";

const char* ENGINE_NAME    = "Kedarium Engine";
const char* ENGINE_VERSION = "0.1";
const char* ENGINE_AUTHOR  = "taintedabomination";
const char* ENGINE_LICENSE = "GNU GPLv3";

void printEngineInfo();
void printVersionInfo();

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    WINDOW_TITLE,
    NULL,
    NULL
  );
  if (window == NULL)
  {
    std::cerr << "Failed to create a GLFW Window!" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Failed to initialize GLEW!" << std::endl;
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    glfwTerminate();
    return -1;
  }

  GLclampf red   = 0.0f;
  GLclampf green = 0.3f;
  GLclampf blue  = 0.3f;
  GLclampf alpha = 1.0f;
  glClearColor(red, green, blue, alpha);

  printEngineInfo();
  printVersionInfo();

  std::string vertexShaderSource = kdr::file::getContents("resources/Shaders/default.vert");
  std::string fragmentShaderSource = kdr::file::getContents("resources/Shaders/default.frag");

  const char* vertexCStringSource = vertexShaderSource.c_str();
  const char* fragmentCStringSource = fragmentShaderSource.c_str();

  std::cout << vertexShaderSource << std::endl;
  std::cout << fragmentShaderSource << std::endl;

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

  GLuint shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cerr << "Failed to link the shader program!" << std::endl;
    std::cerr << "Error: " << infoLog << std::endl;
  }

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void printEngineInfo()
{
  std::cout << ENGINE_NAME << " " << ENGINE_VERSION << std::endl;
  std::cout << "Created by " << ENGINE_AUTHOR << std::endl;
  std::cout << "Licensed under " << ENGINE_LICENSE << std::endl;
}

void printVersionInfo()
{
  std::cout << '\n';
  std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl; 
  std::cout << "GLFW:   " << glfwGetVersionString() << std::endl; 
  std::cout << "GLEW:   " << glewGetString(GLEW_VERSION) << std::endl; 
}
