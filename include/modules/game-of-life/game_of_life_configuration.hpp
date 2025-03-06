#pragma once

#include "common/models/color.hpp"

namespace GameOfLife {

enum StagnationBehaviour { reset, ignore, quit };

struct Configuration {
  float duration;
  Color color;
  bool generateColor;
  bool fade;
  float fadeSpeed;
  StagnationBehaviour onStagnation;

  static Configuration defaults;
};
} // namespace GameOfLife
