#pragma once

#include <map>
#include <string>
#include <vector>

struct ArgParser {
  ArgParser();
  void parse(std::string value);

  std::string name;
  std::map<std::string, std::vector<std::string>> values;
};

// Translates a module name and its parsed FIFO argument map into a CLI11
// command line (e.g. "colors --color=FF0000 --duration=500"), so callers can
// feed it into CLI::App::parse() on the same CLI::App an addFlags() call
// built, instead of re-implementing option parsing by hand.
std::string toCliCommand(std::string moduleName,
                         std::map<std::string, std::vector<std::string>> values);
