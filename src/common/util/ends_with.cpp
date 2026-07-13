#include "common/util/ends_with.hpp"
#include <string>

bool endsWith(std::string const &s, std::string const &pattern) {
  if (s.length() >= pattern.length()) {
    return (0 == s.compare(s.length() - pattern.length(), pattern.length(),
                           pattern));
  } else {
    return false;
  }
}
