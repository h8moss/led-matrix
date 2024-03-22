#pragma once
#include "modules/module_configuration.hpp"

namespace TimeDate {
class Configuration : public ModuleConfiguration {
public:
  Configuration();

  virtual char *getHelp() const override;
  virtual void parseArguments(char **argv, int argc) override;

  virtual ~Configuration();
};
} // namespace TimeDate