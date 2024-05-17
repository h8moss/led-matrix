#pragma once

#include <string>

namespace TimeDate {
struct Configuration {
  std::string font;

  static Configuration defaults;
};
} // namespace TimeDate
