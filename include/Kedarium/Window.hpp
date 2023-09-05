#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace kdr
{
  struct WindowProps
  {
    unsigned int width;
    unsigned int height;
    std::string title;

    WindowProps(
      const unsigned int width,
      const unsigned int height,
      const std::string title
    ) : title(title), width(width), height(height)
    {};
  };

  class Window
  {
    public:
      Window(const WindowProps& windowProps);

      const unsigned int getWidth() const;
      const unsigned int getHeight() const;

      void loop();
      void close();

    protected:
      virtual void update() = 0;
      virtual void render() = 0;

    private:
      GLFWwindow* window;
      unsigned int width;
      unsigned int height;
      std::string title;

      void baseUpdate();
      void baseRender();
  };
}

#endif // WINDOW_HPP
