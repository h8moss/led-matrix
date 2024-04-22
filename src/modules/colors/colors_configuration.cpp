#include "modules/colors/colors_configuration.hpp"
#include "common/util/array_to_vector.hpp"
#include "common/util/debug_log.hpp"
#include "common/util/split_string.hpp"

#include <ctime>

Colors::Configuration::Configuration()
    : ModuleConfiguration(),
      colorGenerationStrategy{Colors::ColorGenerationStrategy::random},
      colors{}, duration{5000}, animationDuration{1000} {
  srand((unsigned int)time(nullptr));
}

char *Colors::Configuration::getHelp() const {
  return "Program to show animations of colors on the full screen\n"
         "Usage: sudo colors.out [options]"
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
         "colors\n"
         "--fade, -f\n"
         "\tMake the colors fade as they are drawn (does nothing for pulse)\n"
         "--once\n"
         "\tThe animation runs only once, and then it exits\n";
}

void Colors::Configuration::parseArguments(char **_, int __) { return; }
void Colors::Configuration::parseData(std::string _) { return; }

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
    } else if (arg == "--fade" || arg == "-f") {
      fading = true;
    } else if (arg == "--once") {
      runOnce = true;
    } else if (arg == "--help" || arg == "-h") {
      showHelp = true;
      return;
    }
  }
}

void Colors::ConfigurationWithAnimation::parseData(std::string data) {
  std::vector<std::string> arguments{split(data, " ")};

  while (arguments.size() != 0) {
    std::vector<std::string> arg{split(arguments[0], ":")};
    arguments.erase(arguments.begin());

    if (arg.size() < 2) {
      dLog("Warning: Value mismatch for argument " + arg[0]);
      continue;
    }

    if (arg[0] == "colors" || arg[0] == "c") {
      std::vector<std::string> splitValues{split(arg[1], ",")};

      for (auto color : splitValues) {
        colors.push_back(Color::fromHex(color));
      }

      colorGenerationStrategy = ColorGenerationStrategy::specific;
    } else if (arg[0] == "duration" || arg[0] == "d") {
      float val{std::stof(arg[1])};

      duration = val;
    } else if (arg[0] == "animation-duration" || arg[1] == "ad") {
      float val{std::stof(arg[1])};

      animationDuration = val;
    } else if (arg[0] == "animation" || arg[0] == "a") {

      if (arg[1] == "pulse")
        animation = Animation::pulse;
      else if (arg[1] == "corners")
        animation = Animation::corners;
      else if (arg[1] == "shrink")
        animation = Animation::shrink;
      else if (arg[1] == "grow")
        animation = Animation::grow;

    } else if (arg[0] == "true-random-colors" || arg[0] == "r") {
      if (arg[1] == "1") {
        colorGenerationStrategy = ColorGenerationStrategy::trueRandom;
      }
    } else if (arg[0] == "fade" || arg[0] == "f") {
      fading = arg[1] == "1";
    } else if (arg[0] == "once") {
      runOnce = arg[1] == "1";
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
