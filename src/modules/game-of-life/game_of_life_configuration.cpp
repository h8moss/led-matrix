#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "common/util/array_to_vector.hpp"

#ifdef DEBUG
#include <iostream>
#endif

GameOfLife::Configuration::Configuration()
    : ModuleConfiguration(), duration{10}, color{}, generateColor{true} {}

char *GameOfLife::Configuration::getHelp() const {
  return "Program to show Conway's game of life on screen\n"
         "Usage: sudo game_of_life.out [options]"
         "\n\n"
         "Options:\n"
         "--color <COLOR>, -c <COLOR>\n"
         "\tPass the color you want the game to be, in HEX (#ff0000)\n"
         "--duration <ms>, -d <ms>\n"
         "\tThe amount of time, in miliseconds a round lasts (default 10)\n";
}

void GameOfLife::Configuration::parseArguments(char **argv, int argc) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};
  while (arguments.size() != 0) {

    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

#ifdef DEBUG
    std::cout << "[DEBUG] Parsing argument: " << arg << std::endl;
#endif

    if (arg == "--duration" || arg == "-d") {
#ifdef DEBUG
      std::cout << "[DEBUG] Argument is --duration" << std::endl;
#endif
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

#ifdef DEBUG
        std::cout << "[DEBUG] Argument value is " << val << std::endl;
#endif

        this->duration = val;
      } else {
        throw "Missing value for --duration flag";
      }
    } else if (arg == "--color" || arg == "-c") {
#ifdef DEBUG
      std::cout << "[DEBUG] Argument --color" << std::endl;
#endif

      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        this->color = Color::fromHex(value);
        this->generateColor = false;

#ifdef DEBUG
        std::cout << "[DEBUG] Argument value is " << value
                  << " which gets parsed as (" << this->color.r << ","
                  << this->color.g << "," << this->color.b << ")" << std::endl;
#endif
      }
    } else if (arg == "--help" || arg == "-h") {
      this->showHelp = true;
      return;
    }
  }

  return;
}
