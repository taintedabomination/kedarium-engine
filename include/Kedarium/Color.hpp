#ifndef COLOR_HPP
#define COLOR_HPP

namespace kdr
{
  namespace color
  {
    /**
     * Represents a color in RGBA (Red, Green, Blue, Alpha) format.
     */
    struct RGBA
    {
      float red;
      float green;
      float blue;
      float alpha;

      /**
       * Constructor for creating an RGBA color.
       *
       * @param red The red component of the color.
       * @param green The green component of the color.
       * @param blue The blue component of the color.
       * @param alpha The alpha (transparency) component of the color.
       */
      RGBA(
        const float red,
        const float green,
        const float blue,
        const float alpha
      ) : red(red), green(green), blue(blue), alpha(alpha)
      {};
    };
  }
}

#endif // COLOR_HPP

