#include "Kedarium/File.hpp"

std::string kdr::file::getContents(std::string path)
{
  std::ifstream file(path);

  if (!file.is_open())
  {
    std::cerr << "Error reading file: " << path << "!" << std::endl; 
    return "";
  }

  std::string fileContents;
  std::string line;
  while (std::getline(file, line)) {
    fileContents += line + '\n';
  }
  file.close();

  return fileContents;
}
