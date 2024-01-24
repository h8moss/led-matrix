#include "colors_configuration.hpp"

#include <random>
#include <ctime>

ColorsModule::ColorsConfiguration::ColorsConfiguration():
  colorGeneration{ColorGenerationStrategy::random},
  colors{},
  duration{5000},
  animationDuration{1000},
  animation{Animation::pulse},
  showHelp{false}
 { 
  srand(time(NULL));
 }

Color ColorsModule::ColorsConfiguration::getColor(Color lastColor) const {
  if (this->colorGeneration == ColorGenerationStrategy::random) {
    int hue{rand() % 360};

    return Color::fromHSL(hue, 1.0f, 0.5f);
  } else if (this->colorGeneration == ColorGenerationStrategy::specific) {
    int index{};
    Color color{colors[index]};
    while (colors.size() != 1 && color.r == lastColor.r && color.g == lastColor.g && color.b == lastColor.b) {
      index = rand() % colors.size();
      color = colors[index];
    }
    return color;
  } else if (this->colorGeneration == ColorGenerationStrategy::trueRandom) {
    int r{rand() % 255};
    int g{rand() % 255};
    int b{rand() % 255};

    return Color{r,g,b};
  }

  return Color::white;
}
