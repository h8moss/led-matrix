#include "common/models/color.hpp"

#include <map>

float hueToRGB(float p, float q, float t) {
  if (t < 0)
    t += 1.0f;
  if (t > 1)
    t -= 1.0f;
  if (t < 0.16666f)
    return p + (q - p) * 6.0f * t;
  if (t < 0.5f)
    return q;
  if (t < 0.66666f)
    return p + (q - p) * (0.66666f - t) * 6.0f;
  return p;
}

Color::Color(int _r, int _g, int _b) : r{_r}, g{_g}, b{_b} {}
Color::Color() : Color(0, 0, 0) {}

Color Color::fromHSL(int h, float s, float l) {
  int r{}, g{}, b{};

  if (s - 1e-5 < 0) { // if s is 0 or close enough
    return Color{(int)(l * 255), (int)(l * 255), (int)(l * 255)};
  }

  float q{l < 0.5f ? l * (1 + s) : l + s - l * s};
  float p{2 * l - q};

  r = (int)(255 * hueToRGB(p, q, ((float)h / 360.0f) + 0.33333f));
  g = (int)(255 * hueToRGB(p, q, ((float)h / 360.0f)));
  b = (int)(255 * hueToRGB(p, q, ((float)h / 360.0f) - 0.33333f));

  return Color{r, g, b};
}

std::map<char, int> hexValues{
    {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},  {'4', 4},  {'5', 5},
    {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9},  {'a', 10}, {'A', 10},
    {'b', 11}, {'B', 11}, {'c', 12}, {'C', 12}, {'d', 13}, {'D', 13},
    {'e', 14}, {'E', 14}, {'f', 15}, {'F', 15},
};

Color Color::fromHex(std::string hex) {
  // Get rid of #
  if (hex[0] == '#') {
    hex = hex.substr(1);
  }

  int r{}, g{}, b{};

  for (char c : hex) {
    if (hexValues.count(c) == 0) {
      throw "Cannot interpret this value as a color: " + hex;
    }
  }

  if (hex.length() == 3) {
    r = hexValues[hex[0]] * 16 + hexValues[hex[0]];
    g = hexValues[hex[1]] * 16 + hexValues[hex[1]];
    b = hexValues[hex[2]] * 16 + hexValues[hex[2]];
  } else if (hex.length() == 6) {
    r = hexValues[hex[0]] * 16 + hexValues[hex[1]];
    g = hexValues[hex[2]] * 16 + hexValues[hex[3]];
    b = hexValues[hex[4]] * 16 + hexValues[hex[5]];
  } else {
    throw "A color must always have 3 or 6 hex characters, " + hex + " has " +
        std::to_string(hex.length());
  }

  return Color{r, g, b};
}

const Color Color::white = {255, 255, 255};
const Color Color::black = {0, 0, 0};
const Color Color::red = {255, 0, 0};
const Color Color::green = {0, 255, 0};
const Color Color::blue = {0, 0, 255};

Color operator*(const Color &c1, float value) {
  return Color((int)((float)c1.r * value), // Red
               (int)((float)c1.g * value), // Green
               (int)((float)c1.b * value)  // Blue
  );
}

rgb_matrix::Color Color::toRGBMatrixColor() {
  return rgb_matrix::Color((uint8_t)r, (uint8_t)g, (uint8_t)b);
}
