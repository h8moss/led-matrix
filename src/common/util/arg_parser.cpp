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

std::string toCliCommand(std::string moduleName,
                         std::map<std::string, std::vector<std::string>> values) {
  std::string command{moduleName};

  for (const auto &entry : values) {
    for (const auto &value : entry.second) {
      command += " --" + entry.first + "=" + value;
    }
  }

  return command;
}
