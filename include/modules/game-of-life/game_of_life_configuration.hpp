#pragma once

#include "modules/module_configuration.hpp"
#include "common/models/color.hpp"

namespace GameOfLife
{
  class Configuration : public ModuleConfiguration
  {
  public:
    Configuration();

    virtual char *getHelp() const override;
    virtual void parseArguments(char **argv, int argc) override;

    int duration;
    Color color;
    bool generateColor;
  };
}
