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

  glEnable(GL_DEPTH_TEST);
  glPointSize(5.f);

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

const GLuint kdr::Window::getBoundShaderID() const
{
  return this->boundShaderID;
}

void kdr::Window::setCamera(kdr::Camera* camera)
{
  this->camera = camera;
}

void kdr::Window::setClearColor(const kdr::color::RGBA& clearColor)
{
  this->clearColor = clearColor;
  glClearColor(
    this->clearColor.red,
    this->clearColor.green,
    this->clearColor.blue,
    this->clearColor.alpha
  );
}

void kdr::Window::_updateDeltaTime()
{
  const float currentTime = glfwGetTime();
  this->deltaTime = currentTime - lastTime;
  this->lastTime = currentTime;
}

void kdr::Window::_updateCamera()
{
  if (this->camera == NULL || this->boundShaderID == 0) return;

  this->camera->handleInputs(this->getWindow(), this->getDeltaTime());
  this->camera->updateMatrices(this->boundShaderID, "cameraMatrix");
}

void kdr::Window::_update()
{
  glfwPollEvents();
  this->_updateDeltaTime();
  this->_updateCamera();
  this->update();
}

void kdr::Window::_render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->render();  
  glfwSwapBuffers(this->window);
}

void kdr::Window::bindShaderID(const GLuint shaderID)
{
  this->boundShaderID = shaderID;
}

void kdr::Window::loop()
{
  while (!glfwWindowShouldClose(this->window))
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
