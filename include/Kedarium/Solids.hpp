#ifndef KDR_SOLIDS_HPP
#define KDR_SOLIDS_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Graphics.hpp"

namespace kdr
{
  namespace Solids
  {
    /**
     * Represents a cube primitive in 3D space.
     */
    class Cube
    {
      public:
        /**
         * Constructs a Cube object with the specified position.
         *
         * @param position The position of the cube in 3D space.
         */
        Cube(glm::vec3 position);
        /**
         * Destructor for the Cube object.
         */
        virtual ~Cube();

        /**
         * Apply the position transformation to the cube.
         *
         * @param shader The shader program to which the position transformation should be applied.
         */
        void ApplyPosition(kdr::Shader& shader);
         /**
          * Render the cube using a shader program.
          *
          * @param shader The shader program used for rendering.
          */
        void Render(kdr::Shader& shader);

      private:
        kdr::VAO* cubeVAO;
        kdr::VBO* cubeVBO;
        kdr::EBO* cubeEBO;

        glm::vec3 position{glm::vec3(0.f, 0.f, 0.f)};
        glm::mat4 model{glm::mat4(1.f)};
    };
  }
}

#endif // KDR_SOLIDS_HPP
