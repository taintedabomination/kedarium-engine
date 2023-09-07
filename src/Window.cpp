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

  this->lastTime = glfwGetTime();
  this->deltaTime = 0.f;

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

  glEnable(GL_DEPTH_TEST);
  glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);
}

GLFWwindow* kdr::Window::getWindow() const
{
  return this->window;
}

const unsigned int kdr::Window::getWidth() const
{
  return this->width;
}

const unsigned int kdr::Window::getHeight() const
{
  return this->height;
}

const float kdr::Window::getDeltaTime() const
{
  return this->deltaTime;
}

void kdr::Window::_updateDeltaTime()
{
  const float currentTime = glfwGetTime();
  this->deltaTime = currentTime - lastTime;
  this->lastTime = currentTime;
}

void kdr::Window::_update()
{
  glfwPollEvents();
  this->_updateDeltaTime();
  this->update();
}

void kdr::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->render();  
  glfwSwapBuffers(this->window);
}

void kdr::Window::loop()
{
  while (!glfwWindowShouldClose(window))
  {
    this->_render();
    this->_update();
  }
}

void kdr::Window::close()
{
  glfwDestroyWindow(this->window);
  glfwTerminate();
}
