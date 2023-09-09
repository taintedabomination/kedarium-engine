#ifndef KDR_CAMERA_HPP
#define KDR_CAMERA_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <string>

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
    float sensitivity;

    /**
     * Constructor for initializing camera properties.
     *
     * @param position The position of the camera in 3D space.
     * @param speed The speed of the camera's movement.
     * @param fov The FOV of the camera.
     * @param aspectRatio The aspect ratio of the camera.
     * @param near The distance of the near clipping plane.
     * @param far The distance of the far clipping plane.
     * @param sensitivity The sensitivity of the camera.
     */
    CameraProps(
      const glm::vec3 position,
      const float speed,
      const float fov,
      const float aspectRatio,
      const float near,
      const float far,
      const float sensitivity
    ) : position(position), speed(speed), fov(fov), aspectRatio(aspectRatio), near(near), far(far), sensitivity(sensitivity)
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
       * Gets the position of the camera in 3D space.
       *
       * @return The position of the camera as a glm::vec3.
       */
      const glm::vec3 getPosition() const;

      /**
       * Handles user inputs for camera control.
       *
       * @param window A pointer to the GLFW window used for input handling.
       * @param deltaTime The time interval since the last frame update.
       */
      void handleInputs(GLFWwindow* window, const float deltaTime);
      /**
       * Updates matrices and set them as a uniform in a shader program.
       *
       * @param programId The ID of the shader program to which the uniforms should be set.
       * @param uniform The name of the uniform variable in the shader program.
       */
      void updateMatrices(GLuint programId, std::string uniform);

    private:
      glm::vec3 position{glm::vec3(0.f)};
      glm::vec3 orientation{glm::vec3(0.f, 0.f, 1.f)};
      glm::vec3 up{glm::vec3(0.f, 1.f, 0.f)};

      float speed{0.f};
      float fov{0.f};
      float aspectRatio{0.f};
      float near{0.f};
      float far{0.f};
      float sensitivity{0.f};

      bool mouseLocked{false};
  };
}

#endif // KDR_CAMERA_HPP
