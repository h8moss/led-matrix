#include "common/util/starts_with.hpp"

bool startsWith(std::string string, std::string pattern) {
  if (pattern.size() > string.size())
    return false;

  for (size_t i{}; i < string.size(); ++i) {
    if (pattern[i] != string[i]) {
      return false;
    }
  }

  return true;
}
