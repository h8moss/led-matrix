#pragma once
#include <string>

class ModuleConfiguration {
public:
  ModuleConfiguration();

  bool showHelp;

  virtual char *getHelp() const = 0;
  virtual void parseArguments(char **argv, int argc) = 0;

  virtual void parseData(std::string data) = 0;

  virtual ~ModuleConfiguration();
};
