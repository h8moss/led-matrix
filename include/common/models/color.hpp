#pragma once

#include <string>

#include "graphics.h"

class Color {
public:
  int r;
  int g;
  int b;

  Color(int _r, int _g, int _b);
  Color();

  /// @brief  Generates a color from HSL values
  /// @param h The hue of the color (0-360)
  /// @param s The saturation of the color (0-1)
  /// @param l The lightness of the color (0-1)
  /// @return The color
  static Color fromHSL(int h, float s, float l);

  static Color fromHex(std::string hex);

  friend Color operator*(const Color &c1, float value);

  rgb_matrix::Color toRGBMatrixColor();

  static const Color white;
  static const Color black;
  static const Color red;
  static const Color green;
  static const Color blue;
};
