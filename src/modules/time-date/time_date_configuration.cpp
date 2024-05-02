#include "modules/time-date/time_date_configuration.hpp"
#include "common/util/array_to_vector.hpp"
#include "common/util/debug_log.hpp"
#include "common/util/split_string.hpp"
#include "modules/module_configuration.hpp"

#include <string>
#include <vector>

TimeDate::Configuration::Configuration() : ModuleConfiguration(), font{"4x6"} {}

const char *TimeDate::Configuration::getHelp() const {
  return "This module displays the time and date acurate to the second"
         "\n\n"
         "Options:\n"
         "--font <FONT>, -f <FONT>\n"
         "\tSet the font to use, the font must be one of the existing fonts, "
         "when passing the font, do not write the extention. (example -f 4x6 "
         "instead of -f 4x6.bdf)"
         "Check out README.md to learn how to add custom fonts\n";
}
void TimeDate::Configuration::parseArguments(char **argv, int argc) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};
  while (arguments.size() != 0) {
    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--font" || arg == "-f") {
      if (arguments.size() > 0) {
        std::string value{arguments[0]};
        this->font = value;
      } else {
        throw "Missing value for --font flag";
      }
    } else if (arg == "--help") {
      showHelp = true;
      return;
    }
  }
}

void TimeDate::Configuration::parseData(std::string data) {
  std::vector<std::string> arguments{split(data, " ")};

  while (arguments.size() > 0) {
    std::vector<std::string> arg{split(arguments[0], ":")};
    arguments.erase(arguments.begin());

    if (arg.size() < 2) {
      dLog("Warning: Argument mismatch for " + arg[0]);
      continue;
    }
  }
}

TimeDate::Configuration::~Configuration() {}
