#include "common/util/arg_parser.hpp"
#include "common/util/split_string.hpp"

ArgParser::ArgParser() : name{}, values{} {}

void ArgParser::parse(std::string value) {
  name = "";
  values = {};

  auto splitValues{split(value, " ")};

  if (splitValues.size() > 0) {
    name = splitValues[0];
  }

  for (size_t i{1}; i < splitValues.size(); i++) {
    auto current{split(splitValues[i], ":")};
    if (current.size() < 2) {
      throw "Missing argument for: " + current[0];
    }
    if (values.count(current[0])) {
      values[current[0]].push_back(current[1]);
    } else {
      values[current[0]] = {current[1]};
    }
  }
}

std::string
ArgParser::ensureSingle(std::map<std::string, std::vector<std::string>> map,
                        std::string key) {
  auto value = map[key];
  if (value.size() != 1) {
    throw std::string{"Expected "} + key + " to be passed only once";
  }
  return value[0];
}

bool ArgParser::ensureBoolean(
    std::map<std::string, std::vector<std::string>> map, std::string key) {
  auto valueVec = map[key];
  auto value = ensureSingle(map, key);
  if (value != "1" && value != "0") {
    throw key + " expected either a 1 or a 0 as it's value";
  }
  return value == "1";
}
