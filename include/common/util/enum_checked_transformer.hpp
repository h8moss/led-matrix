#pragma once

#include "CLI/CLI.hpp"
#include <CLI/CLI.hpp>
#include <map>
#include <string>
#include <vector>

class EnumCheckedTransformer : public CLI::CheckedTransformer {
public:
  EnumCheckedTransformer(std::map<std::string, int> map,
                         std::map<int, std::string> descriptions);
};

struct EnumValueInfo {
  std::string name;
  int value;
  std::string description;
};

// Flattens an enum's name->value and value->description maps (the same maps
// used to build an EnumCheckedTransformer) into a list of {name, value,
// description} triples, so callers don't have to parse them back out of
// CheckedTransformer's generated help text.
std::vector<EnumValueInfo> enumValueInfos(std::map<std::string, int> mapping,
                                          std::map<int, std::string> descriptions);
