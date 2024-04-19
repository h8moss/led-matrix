#pragma once

#include "common/models/color.hpp"
#include "modules/module_configuration.hpp"

namespace GameOfLife {
class Configuration : public ModuleConfiguration {
public:
  Configuration();

  virtual char *getHelp() const override;
  virtual void parseArguments(char **argv, int argc) override;
  virtual void parseData(std::string data) override;

  float duration;
  Color color;
  bool generateColor;
  bool fade;
  float fadeSpeed;
  bool restartOnStagnation;
};
} // namespace GameOfLife
