#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Kedarium/Core.hpp"
#include "Kedarium/Graphics.hpp"

const unsigned int WINDOW_WIDTH  = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char*        WINDOW_TITLE  = "Kedarium Engine";

const GLfloat vertices[] = {
  -0.5f,  -0.5f, 0.f, 1.f, 0.f, 0.f,
   0.0f,  -0.5f, 0.f, 0.f, 1.f, 0.f,
   0.5f,  -0.5f, 0.f, 0.f, 0.f, 1.f,
  -0.25f,  0.0f, 0.f, 1.f, 1.f, 0.f,
   0.25f,  0.0f, 0.f, 0.f, 1.f, 1.f,
   0.0f,   0.5f, 0.f, 1.f, 0.f, 1.f,
};
const GLuint indices[] = {
  0, 1, 3,
  1, 2, 4,
  3, 4, 5,
};

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

  kdr::core::printEngineInfo();
  kdr::core::printVersionInfo();

  kdr::Shader defaultShader("resources/Shaders/default.vert", "resources/Shaders/default.frag");

  GLuint VAO;
  GLuint VBO;
  GLuint EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(GLfloat)), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(GLfloat)), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    defaultShader.Use();
    glBindVertexArray(VAO);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, NULL);
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  defaultShader.Delete();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
