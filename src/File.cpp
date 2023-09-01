#include "Kedarium/File.hpp"

/**
 * Reads the contents of a file into a string.
 *
 * @param path The path to the file to be read.
 * @return A string containing the contents of the file. If an error occurs,
 *         an empty string is returned.
 */
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
