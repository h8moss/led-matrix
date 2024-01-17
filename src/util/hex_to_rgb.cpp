#include "hex_to_rgb.hpp"

#include <map>
#include <iostream>

std::map<char, int> numberMap{
  {'0', 0},
  {'1', 1},
  {'2', 2},
  {'3', 3},
  {'4', 4},
  {'5', 5},
  {'6', 6},
  {'7', 7},
  {'8', 8},
  {'9', 9},
  {'a', 10},
  {'A', 10},
  {'b', 11},
  {'B', 11},
  {'c', 12},
  {'C', 12},
  {'d', 13},
  {'D', 13},
  {'e', 14},
  {'E', 14},
  {'f', 15},
  {'F', 15},
};

std::array<int, 3> hexToRGB(std::string color) {
  while (color[0] == '#') {
    color = color.substr(1);
  }

  if (color.length() == 3) {
    color = color[0] + color[0] + color[1] + color[1] + color[2] + color[2];
  } else if (color.length() != 6) {
    throw  "A hex number must have exactly 6 or 3 digits and may contain a # character at the beginning";
  }

  return {
    numberMap[color[0]]*16 + numberMap[color[1]],
    numberMap[color[2]]*16 + numberMap[color[3]],
    numberMap[color[4]]*16 + numberMap[color[5]],
  };
}