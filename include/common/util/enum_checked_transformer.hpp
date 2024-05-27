#pragma once

#include "CLI/CLI.hpp"
#include <CLI/CLI.hpp>
#include <map>
#include <string>

class EnumCheckedTransformer : public CLI::CheckedTransformer {
public:
  EnumCheckedTransformer(std::map<std::string, int> map,
                         std::map<int, std::string> descriptions);
};
