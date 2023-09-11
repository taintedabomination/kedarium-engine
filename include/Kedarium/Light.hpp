#ifndef KDR_LIGHT_HPP
#define KDR_LIGHT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics.hpp"

namespace kdr {
  /**
   * Represents a light source in the scene.
   */
  class Light
  {
    public:
      /**
       * Constructs a Light object with the specified position and color.
       *
       * @param position The position of the light source in 3D space.
       * @param color The color of the light source as a glm::vec4 (RGBA).
       */
      Light(glm::vec3 position, glm::vec4 color);

      /**
       * Activates the light source in a shader program.
       *
       * @param shader The shader program to which the light should be applied.
       */
      void Use(kdr::Shader& shader);

    private:
      glm::vec3 position;
      glm::vec4 color;
  };
}

#endif // KDR_LIGHT_HPP
