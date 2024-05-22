#pragma once

#include <map>
#include <string>
#include <vector>

struct ArgParser {
  ArgParser();
  void parse(std::string value);

  std::string name;
  std::map<std::string, std::vector<std::string>> values;

  static std::string
  ensureSingle(std::map<std::string, std::vector<std::string>> map,
               std::string key);

  static bool ensureBoolean(std::map<std::string, std::vector<std::string>> map,
                            std::string key);
};
