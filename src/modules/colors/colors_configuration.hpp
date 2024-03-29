#pragma once

#include <vector>
#include "../../common/models/color.hpp"

namespace ColorsModule {

  enum ColorGenerationStrategy {
    random,
    trueRandom,
    specific
  };

  enum Animation {
    pulse,
    corners,
    shrink,
    grow
  };

  class ColorsConfiguration {
    public:
    ColorGenerationStrategy colorGeneration;
    std::vector<Color> colors;
    float duration;
    float animationDuration;
    Animation animation;
    bool showHelp;

    ColorsConfiguration();

    Color getColor(Color lastColor=Color::black) const;
  };

}