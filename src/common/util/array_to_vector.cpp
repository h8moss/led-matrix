#include "common/util/array_to_vector.hpp"
#include <vector>

std::vector<std::string> arrayToVector(int size, char **array) {
  std::vector<std::string> result{};

  for (int i = 0; i < size; i++) {
    char *cString{array[i]};
    std::string newString{cString};
    result.push_back(cString);
  }

  return result;
}
