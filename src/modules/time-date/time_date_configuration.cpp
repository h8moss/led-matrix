#include "modules/time-date/time_date_configuration.hpp"
#include "common/util/array_to_vector.hpp"
#include "modules/module_configuration.hpp"

#include <string>
#include <vector>

TimeDate::Configuration::Configuration() : ModuleConfiguration() {}

char *TimeDate::Configuration::getHelp() const {
  return "This module displays the time and date acurate to the second\n"
         "It does not have any configuration options.\n\n";
}
void TimeDate::Configuration::parseArguments(char **argv, int argc) {
  std::vector<std::string> arguments{arrayToVector(argc, argv)};
  while (arguments.size() != 0) {
    std::string arg{arguments[0]};
    arguments.erase(arguments.begin());

    if (arg == "--help") {
      showHelp = true;
      return;
    }
  }
}

TimeDate::Configuration::~Configuration() {}
