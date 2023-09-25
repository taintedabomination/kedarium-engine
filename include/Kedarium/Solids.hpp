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
        /**
         * Constructs a Solid object with the specified 3D position.
         *
         * @param position The 3D position of the solid as a kdr::XYZ.
         */
        Solid(const kdr::XYZ position);

        /**
         * Sets the position of the solid in 3D space.
         *
         * @param position The new position of the solid as a kdr::XYZ.
         */
        void setPosition(const kdr::XYZ position);

        /**
         * Gets the position of the solid in 3D space.
         *
         * @return The position of the solid as a kdr::XYZ.
         */
        const kdr::XYZ getPosition() const;

        /**
          * Renders the solid using a shader program.
          *
          * @param shader The shader program used for rendering.
          */
        virtual void Render(kdr::Shader& shader) = 0;

      protected:
        kdr::XYZ position{kdr::XYZ(0.f, 0.f, 0.f)};
        glm::mat4 model{glm::mat4(1.f)};

        kdr::VAO* VAO;
        kdr::VBO* VBO;
        kdr::EBO* EBO;

        /**
         * Applies the position transformation to the solid.
         *
         * @param shader The shader program to which the position transformation should be applied.
         */
        void _applyPosition(kdr::Shader& shader);
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
        Cube(const kdr::XYZ position, const float edgeLength);
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
        ColorCube(const kdr::XYZ position, const float edgeLength);
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
        kdr::Color::RGBA color;
    };

    class Plane : public Solid
    {
      public:
        /**
         * Constructs a Plane object with the specified position.
         *
         * @param position The position of the plane in 3D space.
         * @param edgeLength The edge length of the Plane.
         */
        Plane(const kdr::XYZ position, const float edgeLength);
        /**
         * Destructor for the Plane object.
         */
        virtual ~Plane();

         /**
         * Renders the plane using a shader program.
         *
         * @param shader The shader program used for rendering.
         */
        void Render(kdr::Shader& shader);
    };
  }
}

#endif // KDR_SOLIDS_HPP
