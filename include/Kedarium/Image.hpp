#ifndef KDR_IMAGE_HPP
#define KDR_IMAGE_HPP

#include <png.h>
#include <cstring>
#include <string>
#include <iostream>

namespace kdr
{
  namespace Image
  {
    /**
     * Loads an image from a PNG file and returns the image data as a pointer to a character array.
     *
     * @param path The path to the PNG file.
     *
     * @return A pointer to a character array containing the image data, or NULL if an error occurs.
     */
    const bool loadFromPNG(std::string pngPath, unsigned char** data, int& width, int& height);
  }
}

#endif // KDR_IMAGE_HPP
