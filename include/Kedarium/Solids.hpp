#ifndef KDR_SOLIDS_HPP
#define KDR_SOLIDS_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics.hpp"
#include "Color.hpp"

namespace kdr
{
  namespace Solids
  {
    class Solid
    {
      public:
        Solid(const glm::vec3 position);

        /**
         * Sets the position of the solid in 3D space.
         *
         * @param position The new position of the solid as a glm::vec3.
         */
        void setPosition(const glm::vec3 position);

        /**
         * Applies the position transformation to the solid.
         *
         * @param shader The shader program to which the position transformation should be applied.
         */
        void ApplyPosition(kdr::Shader& shader);

        /**
          * Renders the solid using a shader program.
          *
          * @param shader The shader program used for rendering.
          */
        virtual void Render(kdr::Shader& shader) = 0;

      protected:
        glm::vec3 position{glm::vec3(0.f, 0.f, 0.f)};
        glm::mat4 model{glm::mat4(1.f)};
    };

    /**
     * Represents a cube primitive in 3D space.
     */
    class Cube : public Solid
    {
      public:
        /**
         * Constructs a Cube object with the specified position.
         *
         * @param position The position of the cube in 3D space.
         * @param edgeLength The edge length of the Cube.
         */
        Cube(const glm::vec3 position, const float edgeLength);
        /**
         * Destructor for the Cube object.
         */
        virtual ~Cube();

        /**
         * Renders the cube using a shader program.
         *
         * @param shader The shader program used for rendering.
         */
        void Render(kdr::Shader& shader);

      private:
        kdr::VAO* cubeVAO;
        kdr::VBO* cubeVBO;
        kdr::EBO* cubeEBO;
    };

    class ColorCube : public Solid
    {
      public:
        /**
         * Constructs a ColorCube object with the specified position.
         *
         * @param position The position of the cube in 3D space.
         * @param edgeLength The edge length of the ColorCube.
         */
        ColorCube(const glm::vec3 position, const float edgeLength);
        /**
         * Destructor for the ColorCube object.
         */
        virtual ~ColorCube();

        /**
         * Sets the color of the colored cube.
         *
         * @param color The new color of the colored cube as a kdr::Color::RGBA.
         */
        void setColor(const kdr::Color::RGBA color);

        /**
         * Renders the colored cube using a shader program.
         *
         * @param shader The shader program used for rendering.
         */
        void Render(kdr::Shader& shader);

      private:
        kdr::VAO* cubeVAO;
        kdr::VBO* cubeVBO;
        kdr::EBO* cubeEBO;

        kdr::Color::RGBA color;
    };
  }
}

#endif // KDR_SOLIDS_HPP
