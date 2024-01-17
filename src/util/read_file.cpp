#include "read_file.hpp"

#include <fstream>
#include <iostream>

std::string readFileAsText(std::string path) {
  std::ifstream inf{ path.c_str() };
  std::string text{};
  while (inf) {
    inf >> text;
    text += '\n';
  }

  return text;
}

std::vector<std::string> readFileAsLines(std::string path) {
  std::ifstream inf{ path.c_str() };
  std::vector<std::string> result{};
  while (inf) {
    std::string current{};
    inf >> current;
    result.push_back(current);
  }

  return result;
}