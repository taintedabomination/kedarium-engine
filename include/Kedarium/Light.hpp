#ifndef KDR_LIGHT_HPP
#define KDR_LIGHT_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics.hpp"
#include "Color.hpp"
#include "Solids.hpp"

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
      Light(const glm::vec3 position, const kdr::Color::RGBA color);

      /**
       * Sets the position of the light source in 3D space.
       *
       * @param position The new position of the light source as a glm::vec3.
       */
      void setPosition(const glm::vec3 position);
      /**
       * Sets the color of the light source.
       *
       * @param color The new color of the light source as a kdr::Color::RGBA.
       */
      void setColor(const kdr::Color::RGBA color);
      /**
       * Sets the solid object associated with the light source.
       *
       * @param solid A pointer to the solid object to be associated with the light.
       */
      void setSolid(kdr::Solids::Solid* solid);

      /**
       * Activates the light source in a shader program.
       *
       * @param shader The shader program to which the light should be applied.
       */
      void Use(kdr::Shader& shader);
      /**
       * Renders the light source as a solid object using a shader program.
       *
       * @param shader The shader program used for rendering the light as a solid object.
       */
      void RenderSolid(kdr::Shader& shader);

    private:
      glm::vec3 position;
      kdr::Color::RGBA color;
      kdr::Solids::Solid* solid;
  };
}

#endif // KDR_LIGHT_HPP
