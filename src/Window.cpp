#include "Kedarium/Window.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

kdr::Window::Window(const WindowProps& windowProps)
{
  this->width = windowProps.width;
  this->height = windowProps.height;
  this->title = windowProps.title;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window = glfwCreateWindow(
    this->width,
    this->height,
    this->title.c_str(),
    NULL,
    NULL
  );
  if (window == NULL)
  {
    std::cerr << "Failed to create a GLFW Window!" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Failed to initialize GLEW!" << std::endl;
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    glfwTerminate();
  }

  GLclampf red   = 0.0f;
  GLclampf green = 0.3f;
  GLclampf blue  = 0.3f;
  GLclampf alpha = 1.0f;
  glClearColor(red, green, blue, alpha);

  glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);
}

const unsigned int kdr::Window::getWidth() const
{
  return this->width;
}
const unsigned int kdr::Window::getHeight() const
{
  return this->height;
}

void kdr::Window::baseUpdate()
{
  glfwPollEvents();
  this->update();
}

void kdr::Window::baseRender()
{
  glClear(GL_COLOR_BUFFER_BIT);
  this->render();  
  glfwSwapBuffers(this->window);
}

void kdr::Window::loop()
{
  while (!glfwWindowShouldClose(window))
  {
    this->baseUpdate();
    this->baseRender();
  }
}

void kdr::Window::close()
{
  glfwDestroyWindow(this->window);
  glfwTerminate();
}
