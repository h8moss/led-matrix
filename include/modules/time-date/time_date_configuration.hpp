#pragma once
#include "modules/module_configuration.hpp"

#include <string>

namespace TimeDate {
class Configuration : public ModuleConfiguration {
public:
  Configuration();

  virtual const char *getHelp() const override;
  virtual void parseArguments(char **argv, int argc) override;
  virtual void parseData(std::string data) override;

  std::string font;

  virtual ~Configuration();
};
} // namespace TimeDate
