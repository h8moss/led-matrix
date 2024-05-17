#pragma once
#include "common/models/color.hpp"

#include <vector>

namespace Colors {

enum Animation { pulse, corners, shrink, grow };

struct Configuration {
  bool useTrueRandomColors;
  std::vector<Color> colors;
  float duration;
  float animationDuration;
  bool fading;
  bool runOnce;

  static Configuration defaults;

  Color getColor(Color lastColor = Color::black) const;
};

struct ConfigurationWithAnimation : public Configuration {
  Animation animation;

  static ConfigurationWithAnimation defaults;

  static std::map<std::string, Animation> animationMap;
};
} // namespace Colors
