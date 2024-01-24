#pragma once

#include <string>

#include "led-matrix.h"

class Color {
  public:
  int r;
  int g;
  int b;

  Color(int _r, int _g, int _b);

  void setCanvasPixel(int x, int y, rgb_matrix::Canvas *canvas);

  /// @brief  Generates a color from HSL values
  /// @param h The hue of the color (0-360)
  /// @param s The saturation of the color (0-1)
  /// @param l The lightness of the color (0-1)
  /// @return The color
  static Color fromHSL(int h, float s, float l);

  static Color fromHex(std::string hex);

  static const Color white;
  static const Color black;
  static const Color red;
  static const Color green;
  static const Color blue;
};