#pragma once
#include "modules/module_configuration.hpp"

#include <string>

namespace TimeDate {
class Configuration : public ModuleConfiguration {
public:
  Configuration();

  virtual char *getHelp() const override;
  virtual void parseArguments(char **argv, int argc) override;

  std::string font;

  virtual ~Configuration();
};
} // namespace TimeDate
