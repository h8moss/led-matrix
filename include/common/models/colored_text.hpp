#pragma once

#include "common/models/color.hpp"

class ColoredText {
public:
  ColoredText(Color _color, std::string _text) : color{_color}, text{_text} {}

  Color color;
  std::string text;
};
