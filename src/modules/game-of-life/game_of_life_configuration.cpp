#include "modules/game-of-life/game_of_life_configuration.hpp"
#include "common/util/array_to_vector.hpp"
#include "common/util/debug_log.hpp"
#include "common/util/split_string.hpp"

#include <vector>

GameOfLife::Configuration::Configuration()
    : ModuleConfiguration(), duration{10}, color{}, generateColor{true},
      fade{false}, fadeSpeed{0.1f},
      onStagnation{GameOfLife::StagnationBehaviour::reset} {}

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
         "default is 0.1\n"
         "--stagnation\n"
         "\tWhat the game should do if it encounters stagnation (repeated "
         "game)\n"
         "\t\treset (default): Restarts the game with a random state on "
         "stagnation\n"
         "\t\tquit: Exits the game on stagnation\n"
         "\t\tignore: The game continues even if stagnant\n";
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
    } else if (arg == "--stagnation") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());
        if (value == "reset") {
          onStagnation = StagnationBehaviour::reset;
        } else if (value == "quit") {
          onStagnation = StagnationBehaviour::quit;
        } else if (value == "ignore") {
          onStagnation = StagnationBehaviour::ignore;
        } else {
          throw "Unrecognized flag value for --stagnation: " + value;
        }
      } else {
        throw "Missing value for --stagnation flag";
      }
    } else if (arg == "--fade" || arg == "-f") {
      this->fade = true;
    } else if (arg == "--help" || arg == "-h") {
      this->showHelp = true;
      return;
    }
  }
}

void GameOfLife::Configuration::parseData(std::string data) {
  std::vector<std::string> arguments{split(data, " ")};
  while (arguments.size() != 0) {

    std::vector<std::string> arg{split(arguments[0], ":")};
    arguments.erase(arguments.begin());

    if (arg.size() < 2) {
      dLog("Warning: Value mismatch for argument " + arg[0]);
      continue;
    }

    if (arg[0] == "duration" || arg[0] == "d") {
      float val{std::stof(arg[1])};

      this->duration = val;
    } else if (arg[0] == "color" || arg[0] == "c") {

      this->color = Color::fromHex(arg[1]);
      this->generateColor = false;

    } else if (arg[0] == "fade-speed" || arg[0] == "s") {

      float val{std::stof(arg[1])};

      this->fadeSpeed = val;
    }

    else if (arg[0] == "stagnation") {
      if (arg[1] == "reset") {
        onStagnation = StagnationBehaviour::reset;
      } else if (arg[1] == "quit") {
        onStagnation = StagnationBehaviour::quit;
      } else if (arg[1] == "ignore") {
        onStagnation = StagnationBehaviour::ignore;
      } else {
        throw "Unrecognized flag value for stagnation: " + arg[1];
      }
    } else if (arg[0] == "fade" || arg[0] == "f") {
      this->fade = arg[1] == "1";
    }
  }
}
