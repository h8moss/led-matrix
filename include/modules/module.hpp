#pragma once
#include "common/util/better_canvas.hpp"

#include "CLI/CLI.hpp"

#include <string>

class Module {
public:
  Module(BetterCanvas *_canvas) : canvas{_canvas} {}

  std::string name;
  std::string description;

  virtual void setup() = 0;
  virtual long int render() = 0;
  virtual void teardown() = 0;

  virtual void addFlags(CLI::App *app) = 0;

  virtual ~Module() {
    delete canvas;

    canvas = nullptr;
  }

protected:
  BetterCanvas *canvas = nullptr;
};
