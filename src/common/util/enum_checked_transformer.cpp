#include "common/util/enum_checked_transformer.hpp"
#include "CLI/CLI.hpp"

EnumCheckedTransformer::EnumCheckedTransformer(
    std::map<std::string, int> map, std::map<int, std::string> descriptions)
    : CLI::CheckedTransformer(map, CLI::ignore_case) {

  this->desc_function_ = [map, descriptions]() {
    std::ostringstream out;

    out << "\n";
    for (const auto &entry : map) {
      out << "\t\t" << entry.first << ": " << descriptions.at(entry.second)
          << '\n';
    }
    out << "\tOR: ";
    bool first{true};
    for (const auto &entry : map) {
      if (!first) {
        out << ", ";
      }
      first = false;
      out << entry.second << "->" << entry.first;
    }
    return out.str();
  };
}
