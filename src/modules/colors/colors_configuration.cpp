#include "modules/colors/colors_configuration.hpp"
#include "common/util/debug_log.hpp"

Colors::Configuration Colors::Configuration::defaults = {
    .useTrueRandomColors = false,
    .colors = {},
    .duration = 5000,
    .animationDuration = 1000,
    .fading = false,
    .runOnce = false};

static Colors::ConfigurationWithAnimation _createConfigurationWithAnimation() {
  Colors::ConfigurationWithAnimation defaults{};

  static_cast<Colors::Configuration>(defaults) =
      Colors::Configuration::defaults;

  dLog("Logging defaults");
  dLog(defaults.duration);
  dLog(Colors::Configuration::defaults.duration);

  defaults.animation = Colors::Animation::pulse;

  return static_cast<Colors::ConfigurationWithAnimation>(defaults);
}

Colors::ConfigurationWithAnimation
    Colors::ConfigurationWithAnimation::defaults =
        _createConfigurationWithAnimation();

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
