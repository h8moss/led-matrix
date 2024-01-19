#include "parse_arguments.hpp"
#include "../../common/util/array_to_vector.hpp"

using namespace GameOfLifeModule;

GameOfLifeConfiguration GameOfLifeModule::parseArguments(int argc, char **argv) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};
  GameOfLifeConfiguration config{};

  while (arguments.size() != 0) {
    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--duration" || arg == "-d") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        config.duration = val;
      } else {
        throw "Missing value for --duration flag";
      }
    } else if (arg == "--color" || arg == "-c") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        config.color = Color::fromHex(value);
        config.generateColor = false;
      }
    } else if (arg == "--help" || arg == "-h") {
      config.showHelp = true;
      return config;
    }
  }

  return config;
}

