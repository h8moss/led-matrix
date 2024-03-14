#include "common/util/split_string.hpp"

std::vector<std::string> split(std::string value, std::string delimiter) {

  std::vector<std::string> result{};

  size_t pos = 0;
  std::string token;
  while ((pos = value.find(delimiter)) != std::string::npos) {
    token = value.substr(0, pos);
    result.push_back(token);
    value.erase(0, pos + delimiter.length());
  }
  result.push_back(value);

  return result;
}
