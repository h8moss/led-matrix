#include "common/util/starts_with.hpp"
#include "common/util/debug_log.hpp"

bool startsWith(std::string string, std::string pattern) {
  dLog("Comparing " + string + " to " + pattern);
  if (pattern.size() > string.size())
    return false;

  for (size_t i{}; i < pattern.size(); ++i) {
    if (pattern[i] != string[i]) {
      return false;
    }
  }

  return true;
}
