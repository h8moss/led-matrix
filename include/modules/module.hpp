#pragma once
#include "common/canvas/icanvas.hpp"
#include "common/util/enum_checked_transformer.hpp"

#include "CLI/CLI.hpp"

#include <map>
#include <string>

class Module {
public:
  Module(ICanvas *_canvas, std::string _name, std::string _description)
      : canvas{_canvas}, name{_name}, description{_description} {}

  std::string name;
  std::string description;

  virtual void setup() = 0;
  virtual long int render() = 0;
  virtual void teardown() = 0;

  virtual void addFlags(CLI::App *app) = 0;
  virtual void resetToDefaults() = 0;

  const std::map<CLI::Option *, std::vector<EnumValueInfo>> &getEnumOptions() const {
    return enumOptionValues;
  }

  virtual ~Module() {}

protected:
  ICanvas *canvas = nullptr;
  std::map<CLI::Option *, std::vector<EnumValueInfo>> enumOptionValues;

  // Registers an enum-backed option, wiring it up exactly like
  // add_option(...)->transform(EnumCheckedTransformer(...)) while also
  // retaining the same name/value/description data for introspection (e.g.
  // by led-matrix-info), since CLI11 has no public API to recover that data
  // back out of a Transformer once attached.
  template <typename EnumT>
  CLI::Option *addEnumOption(CLI::App *cmd, std::string flagNames, EnumT &target,
                             std::string description,
                             std::map<std::string, int> mapping,
                             std::map<int, std::string> descriptions) {
    auto option = cmd->add_option(flagNames, target, description)
                      ->transform(EnumCheckedTransformer(mapping, descriptions));
    enumOptionValues[option] = enumValueInfos(mapping, descriptions);
    return option;
  }
};
