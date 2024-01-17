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

  if (color.length() != 6 && color.length() != 3) {
    throw "A hex number must have exactly 6 or 3 digits and may contain a # character at the beginning, " + color + " contains " + std::to_string(color.length());
  }

  char r1{};
  char g1{};
  char b1{};

  char r2{};
  char g2{};
  char b2{};

  if (color.length() == 3) {
    r1 = color.at(0);
    r2 = color.at(0);
    g1 = color.at(1);
    g2 = color.at(1);
    b1 = color.at(2);
    b2 = color.at(2);
  } else {
    r1 = color.at(0);
    r2 = color.at(1);
    g1 = color.at(2);
    g2 = color.at(3);
    b1 = color.at(4);
    b2 = color.at(5);
  }

  return {
    numberMap[r1]*16 + numberMap[r2],
    numberMap[g1]*16 + numberMap[g2],
    numberMap[b1]*16 + numberMap[b2],
  };
}