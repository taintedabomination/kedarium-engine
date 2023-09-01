#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <iostream>
#include <string>

namespace kdr
{
  namespace file
  {
    std::string getContents(std::string path);
  }
}

#endif // FILE_HPP
