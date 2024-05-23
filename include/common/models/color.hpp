#pragma once

#include <Magick++/Color.h>
#include <string>

#include "graphics.h"

struct Color {
  int r;
  int g;
  int b;

  Color(int _r, int _g, int _b);
  Color();

  const std::string string() const;

  /// @brief  Generates a color from HSL values
  /// @param h The hue of the color (0-360)
  /// @param s The saturation of the color (0-1)
  /// @param l The lightness of the color (0-1)
  /// @return The color
  static Color fromHSL(int h, float s, float l);

  static Color fromHex(std::string hex);

  static Color fromMagickColor(Magick::Color c);

  friend Color operator*(const Color &c1, float value);

  bool operator==(const Color &color) const;

  rgb_matrix::Color toRGBMatrixColor();

  static const Color white;
  static const Color black;
  static const Color red;
  static const Color green;
  static const Color blue;
};

bool lexical_cast(const std::string &input, Color &v);
