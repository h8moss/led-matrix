#include "modules/images/images_configuration.hpp"
#include "common/util/array_to_vector.hpp"
#include "modules/module_configuration.hpp"
#include <string>

Images::Configuration::Configuration()
    : ModuleConfiguration(), imageData{}, fit{}, xAlignment{}, yAlignment{},
      exitOnEnd{}, shuffleImages{} {}

const char *Images::Configuration::getHelp() const {
  return "Display an arbitrary image\n\n"
         "Options: \n"
         "--duration <ms>, -d <ms>\n"
         "\tThe amount of time the images should appear, works for every "
         "images passed AFTER this flag, and can be passed multiple times \n"
         "--image <path>, -i <path>\n"
         "\tThe path to an image\n"
         "--fps <value>\n"
         "\tIf passed, all --duration flags will be ignored and instead the "
         "images will be played at the fps specified\n"
         "--alignment <value>, -a\n"
         "\tHow the image should be aligned to the canvas, this can also be "
         "set for each axis individually using --alignment-x  or --ax and "
         "--alignment-y or --ay \n"
         "\t\t- leading (default)\n"
         "\t\t- center\n"
         "\t\t- trailing\n"
         "--fit <value>, -f <value>\n"
         "\tHow the image should fit into the canvas, in case it's smaller or "
         "bigger than it\n"
         "\t\t- stretch (default): Fits both sides into the canvas by "
         "stretching\n"
         "\t\t- crop: Fits the smallest side into the canvas\n"
         "\t\t- box: Fits the largest side into the canvas\n"
         "--once\n"
         "\tPlays the animation once and exits"
         "--shuffle\n"
         "\tPlays the images in a random order";
}

void Images::Configuration::parseArguments(char **argv, int argc) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};

  int currentDuration{-1};

  while (arguments.size() != 0) {
    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--duration" || arg == "-d") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        arguments.erase(arguments.begin());

        currentDuration = std::stoi(value);
      } else {
        throw "Missing value for --duration flag";
      }
    } else if (arg == "--image" || arg == "-i") {
      std::string
    }
  }
}
