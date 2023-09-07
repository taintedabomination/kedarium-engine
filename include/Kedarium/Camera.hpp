#ifndef KDR_CAMERA_HPP
#define KDR_CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace kdr
{
  /**
   * Struct to store camera properties.
   */
  struct CameraProps
  {
    glm::vec3 position;
    float speed;
    float fov;
    float aspectRatio;
    float near;
    float far;

    /**
     * Constructor for initializing camera properties.
     * @param position The position of the camera in 3D space.
     * @param speed The speed of the camera's movement.
     * @param fov The FOV of the camera.
     * @param aspectRatio The aspect ratio of the camera.
     * @param near The distance of the near clipping plane.
     * @param far The distance of the far clipping plane.
     */
    CameraProps(
      const glm::vec3 position,
      const float speed,
      const float fov,
      const float aspectRatio,
      const float near,
      const float far
    ) : position(position), speed(speed), fov(fov), aspectRatio(aspectRatio), near(near), far(far)
    {};
  };

  class Camera
  {
    public:
      /**
       * Constructs a Camera object with the specified camera properties.
       *
       * @param cameraProps The properties for configuring the camera.
       */
      Camera(const CameraProps& cameraProps);

      /**
       * Get the position of the camera in 3D space.
       *
       * @return The position of the camera as a glm::vec3.
       */
      const glm::vec3 getPosition() const;

      /**
       * Handle user inputs for camera control.
       *
       * @param window A pointer to the GLFW window used for input handling.
       */
      void handleInputs(GLFWwindow* window);

    private:
      glm::vec3 position;
      glm::vec3 orientation;

      float speed;
      float fov;
      float aspectRatio;
      float near;
      float far;
  };
}

#endif // KDR_CAMERA_HPP
