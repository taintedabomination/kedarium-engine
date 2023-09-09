#ifndef KDR_WINDOW_HPP
#define KDR_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Camera.hpp"
#include "Color.hpp"

namespace kdr
{
  /**
   * Struct to store window properties.
   */
  struct WindowProps
  {
    unsigned int width;
    unsigned int height;
    std::string title;

    /**
     * Constructor for initializing window properties.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The title of the window.
     */
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
      /**
       * Constructs a Window object with the specified properties.
       *
       * @param windowProps The properties for configuring the window.
       */
      Window(const WindowProps& windowProps);

      /**
       * GetS a pointer to the GLFW window associated with the object.
       *
       * @return A pointer to the GLFW window.
       */
      GLFWwindow* getWindow() const;
      /**
       * Gets the width of the window.
       * 
       * @return The width of the window.
       */
      const unsigned int getWidth() const;
      /**
       * Gets the height of the window.
       * 
       * @return The height of the window.
       */
      const unsigned int getHeight() const;
      /**
       * Gets the delta time of the window.
       * 
       * @return The delta time of the window.
       */
      const float getDeltaTime() const;
      /**
       * Gets the ID of the currently bound shader program.
       *
       * @return The ID of the currently bound shader program.
       */
      const GLuint getBoundShaderID() const;

      /**
       * Sets the camera to be used for rendering.
       *
       * @param camera The Camera object to set as the active camera.
       */
      void setCamera(kdr::Camera* camera);
      /**
       * Sets the clear color for the window.
       *
       * @param clearColor The RGBA color to set as the clear color.
       */
      void setClearColor(const kdr::Color::RGBA& clearColor);

      /**
       * Binds a shader program for rendering.
       *
       * @param shaderID The ID of the shader program to bind.
       */
      void bindShaderID(const GLuint shaderID);
      /**
       * Main loop for the window.
       */
      void loop();
      /**
       * Closes the window.
       */
      void close();

    protected:
      /**
       * Update function (to be overridden by derived classes).
       */
      virtual void update() = 0;
      /**
       * Render function (to be overridden by derived classes).
       */
      virtual void render() = 0;

    private:
      GLFWwindow* window;
      unsigned int width{800};
      unsigned int height{600};
      std::string title{"Kedarium Engine"};
      kdr::Camera* camera{NULL};
      GLuint boundShaderID{0};

      float lastTime{(float)glfwGetTime()};
      float deltaTime{0.f};

      kdr::Color::RGBA clearColor = kdr::Color::RGBA(
        0.f,
        0.f,
        0.f,
        1.f
      );

      /**
       * Updates the time difference between frames (delta time).
       */
      void _updateDeltaTime();
      /**
       * Updates the camera's internal state.
       */
      void _updateCamera();
      /**
       * Base function for updating the window.
       */
      void _update();
      /**
       * Base function for rendering the window.
       */
      void _render();
  };
}

#endif // KDR_WINDOW_HPP
