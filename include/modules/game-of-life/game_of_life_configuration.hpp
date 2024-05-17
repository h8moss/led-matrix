#pragma once

#include "common/models/color.hpp"
#include <map>

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

  static std::map<std::string, StagnationBehaviour> stagnationBehaviourMap;
};
} // namespace GameOfLife
