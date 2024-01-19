#include "parse_arguments.hpp"
#include "../../common/util/split_string.hpp"

#include <iostream>

using namespace ColorsModule;

/*
    * --colors=#FFF,#028,... (also -c)
    * --duration=ms // time a color stays (-d)
    * --animation-duration=ms (--ad)
    * --animation=animation (-a)
      * pulse
      * corner to corner
      * walk left to right
      * the old color becomes smaller and smaller and the new color comes from the sides
    * --true-random-colors (-r)
      * normally, we generate specific, fully illuminated colors, if this is passed, the colors are actually random
    * --help, -h
*/

ColorsConfiguration ColorsModule::parseArguments(int argc, char** args) {
  std::vector<std::string> arguments{arrayToVector(argc, args)};
  
  ColorsConfiguration config{};

  while (arguments.size() != 0) {
    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--colors" || arg == "-c") {
      if (arguments.size() > 0) {
        std::string values{arguments[0]};
        arguments.erase(arguments.begin());

        std::vector<std::string> splitValues{split(values, ",")};

        for (auto color : splitValues) {
          config.colors.push_back(Color::fromHex(color));
        }

        config.colorGeneration = ColorGenerationStrategy::specific;
      } else {
        throw "Missing value for --colors flag";
      }
    } else if (arg == "--duration" || arg == "-d") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        config.duration = val;
      } else {
        throw "Missing value for --duration flag";
      }
    } else if (arg == "--animation-duration" || arg == "--ad") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        config.animationDuration = val;
      } else {
        throw "Missing value for --animation-duration flag";
      }
    } else if (arg == "--animation" || arg == "-a") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        if (value == "pulse")  config.animation = Animation::pulse;
        else if (value == "corners") config.animation = Animation::corners;
        else if (value == "shrink") config.animation = Animation::shrink;
        else if (value == "grow") config.animation = Animation::grow;
        else {
          throw "Unrecognized --animation value";
        }
      } else {
        throw "Missing value for --animation flag";
      }
    } else if (arg == "--true-random-colors" || arg == "-r") {
      config.colorGeneration = ColorGenerationStrategy::trueRandom;
    } else if (arg == "--help" || arg == "-h") {
      config.showHelp = true;
      return config; // Stop checking args and show help
    } else {
      std::cout << "Unrecognized flag " << arg << '\n';
    }
  }

  return config;
}