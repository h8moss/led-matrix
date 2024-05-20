#include "modules/colors/colors_configuration.hpp"
#include "common/util/debug_log.hpp"

Colors::ConfigurationWithAnimation::ConfigurationWithAnimation(
    Configuration config, Animation anim)
    : Configuration{config}, animation{anim} {}

Colors::Configuration Colors::Configuration::defaults = {
    .useTrueRandomColors = false,
    .colors = {},
    .duration = 5000,
    .animationDuration = 1000,
    .fading = false,
    .runOnce = false};

Colors::ConfigurationWithAnimation
    Colors::ConfigurationWithAnimation::defaults =
        Colors::ConfigurationWithAnimation(Colors::Configuration::defaults,
                                           Colors::Animation::pulse);

std::map<std::string, Colors::Animation>
    Colors::ConfigurationWithAnimation::animationMap = {
        {"grow", Colors::Animation::grow},
        {"pulse", Colors::Animation::pulse},
        {"shrink", Colors::Animation::shrink},
        {"corners", Colors::Animation::corners}};

Color Colors::Configuration::getColor(Color lastColor) const {
  if (!useTrueRandomColors && colors.size() == 0) {
    int hue{rand() % 360};
    return Color::fromHSL(hue, 1.0f, 0.5f);
  } else if (colors.size() != 0) {
    int index{};
    Color color{colors[index]};
    while (colors.size() != 1 && color.r == lastColor.r &&
           color.g == lastColor.g && color.b == lastColor.b) {
      index = rand() % colors.size();
      color = colors[index];
    }
    return color;
  } else if (useTrueRandomColors) {
    int r{rand() % 255};
    int g{rand() % 255};
    int b{rand() % 255};

    return Color{r, g, b};
  }

  return Color::white;
}
