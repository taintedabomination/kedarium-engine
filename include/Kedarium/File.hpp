#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace kdr
{
  namespace file
  {
    /**
     * Reads the contents of a file into a string.
     *
     * @param path The path to the file to be read.
     * @return A string containing the contents of the file. If an error occurs,
     *         an empty string is returned.
     */
    std::string getContents(std::string path);
  }
}

#endif // FILE_HPP
