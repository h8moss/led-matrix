#include "modules/colors/colors_configuration.hpp"
#include "common/util/array_to_vector.hpp"
#include "common/util/split_string.hpp"

#include <ctime>

Colors::Configuration::Configuration()
    : ModuleConfiguration(),
      colorGenerationStrategy{Colors::ColorGenerationStrategy::random},
      colors{}, duration{5000}, animationDuration{1000} {
  srand((unsigned int)time(nullptr));
}

const char *Colors::Configuration::getHelp() const {
  return "Module to show animations of colors on the full screen"
         "\n\n"
         "Options:\n"
         "--colors <COLORS>, -c <COLORS>\n"
         "\tPass a list of colors you want the screen to cycle through\n"
         "--duration <ms>, -d <ms>\n"
         "\tThe amount of time, in miliseconds a color should remain on the "
         "screen (default 5000)\n"
         "--animation <ANIMATION>, -a <ANIMATION>\n"
         "\tThe animation to show, should be one of the following values:\n"
         "\t\tpulse (default) - A color pulses on the screen\n"
         "\t\tcorners - A color moves from one corner to the opposite\n"
         "\t\tshrink - The last color shrinks to the center of the screen\n"
         "\t\tgrow - The next color grows from the center of the screen\n"
         "--animation-duration <ms>, --ad <ms>\n"
         "\tThe amount of time, in miliseconds the transition between colors "
         "should last (default 1000)\n"
         "--true-random-colors, -r\n"
         "\tNormally, the screen only shows fully saturated, medium lightness "
         "colors, passing this flag makes the screen show truly randomized "
         "colors\n";
}

void Colors::Configuration::parseArguments(char **_, int __) { return; }

void Colors::ConfigurationWithAnimation::parseArguments(char **argv, int argc) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};

  while (arguments.size() != 0) {
    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--colors" || arg == "-c") {
      if (arguments.size() > 0) {
        std::string values{arguments[0]};
        arguments.erase(arguments.begin());

        std::vector<std::string> splitValues{split(values, ",")};

        for (auto color : splitValues) {
          colors.push_back(Color::fromHex(color));
        }

        colorGenerationStrategy = ColorGenerationStrategy::specific;
      } else {
        throw "Missing value for --colors flag";
      }
    } else if (arg == "--duration" || arg == "-d") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        duration = val;
      } else {
        throw "Missing value for --duration flag";
      }
    } else if (arg == "--animation-duration" || arg == "--ad") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        animationDuration = val;
      } else {
        throw "Missing value for --animation-duration flag";
      }
    } else if (arg == "--animation" || arg == "-a") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        if (value == "pulse")
          animation = Animation::pulse;
        else if (value == "corners")
          animation = Animation::corners;
        else if (value == "shrink")
          animation = Animation::shrink;
        else if (value == "grow")
          animation = Animation::grow;
        else {
          throw "Unrecognized --animation value";
        }
      } else {
        throw "Missing value for --animation flag";
      }
    } else if (arg == "--true-random-colors" || arg == "-r") {
      colorGenerationStrategy = ColorGenerationStrategy::trueRandom;
    } else if (arg == "--help" || arg == "-h") {
      showHelp = true;
      return;
    }
  }
}

Color Colors::Configuration::getColor(Color lastColor) const {
  if (colorGenerationStrategy == ColorGenerationStrategy::random) {
    int hue{rand() % 360};
    return Color::fromHSL(hue, 1.0f, 0.5f);
  } else if (colorGenerationStrategy == ColorGenerationStrategy::specific) {
    int index{};
    Color color{colors[index]};
    while (colors.size() != 1 && color.r == lastColor.r &&
           color.g == lastColor.g && color.b == lastColor.b) {
      index = rand() % colors.size();
      color = colors[index];
    }
    return color;
  } else if (colorGenerationStrategy == ColorGenerationStrategy::trueRandom) {
    int r{rand() % 255};
    int g{rand() % 255};
    int b{rand() % 255};

    return Color{r, g, b};
  }

  return Color::white;
}

Colors::ConfigurationWithAnimation::ConfigurationWithAnimation()
    : Configuration(), animation{Animation::pulse} {}

Colors::Configuration::~Configuration() {}
Colors::ConfigurationWithAnimation::~ConfigurationWithAnimation() {}
