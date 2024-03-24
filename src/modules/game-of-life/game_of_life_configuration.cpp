#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "common/util/array_to_vector.hpp"

GameOfLife::Configuration::Configuration()
    : ModuleConfiguration(), duration{10}, color{}, generateColor{true},
      fade{false}, fadeSpeed{} {}

char *GameOfLife::Configuration::getHelp() const {
  return "Program to show Conway's game of life on screen\n"
         "Usage: sudo game_of_life.out [options]"
         "\n\n"
         "Options:\n"
         "--color <COLOR>, -c <COLOR>\n"
         "\tPass the color you want the game to be, in HEX (#ff0000)\n"
         "--duration <ms>, -d <ms>\n"
         "\tThe amount of time, in miliseconds a round lasts (default 10)\n"
         "--fade, -f\n"
         "\tAdd a fading effect to dying cells\n"
         "--fade-speed, -s\n"
         "\tThe speed by which fade occurs, a number between 0.0 and 1.0, "
         "default is 0.1";
}

void GameOfLife::Configuration::parseArguments(char **argv, int argc) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};
  while (arguments.size() != 0) {

    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--duration" || arg == "-d") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        this->duration = val;
      } else {
        throw "Missing value for --duration flag";
      }
    } else if (arg == "--color" || arg == "-c") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        this->color = Color::fromHex(value);
        this->generateColor = false;

      } else {
        throw "Missing value for --color flag";
      }
    } else if (arg == "--fade-speed" || arg == "-s") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        float val{std::stof(value)};

        this->fadeSpeed = val;
      } else {
        throw "Missing value for --fade-speed flag";
      }
    } else if (arg == "--fade" || arg == "-f") {
      this->fade = true;
    } else if (arg == "--help" || arg == "-h") {
      this->showHelp = true;
      return;
    }
  }
}
