#pragma once
#include "common/util/better_canvas.hpp"
#include "modules/module_configuration.hpp"

#include <string>

class Module {
public:
  Module(BetterCanvas *_canvas, ModuleConfiguration *config)
      : configuration{config}, canvas{_canvas} {}

  std::string name;
  std::string description;

  virtual void setup() = 0;
  virtual long int render() = 0;
  virtual void teardown() = 0;
  ModuleConfiguration *configuration;

  virtual ~Module() {
    delete canvas;
    delete configuration;

    canvas = nullptr;
    configuration = nullptr;
  }

protected:
  BetterCanvas *canvas = nullptr;
};
