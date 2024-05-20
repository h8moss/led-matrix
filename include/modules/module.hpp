#pragma once
#include "common/canvas/icanvas.hpp"

#include "CLI/CLI.hpp"

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

  virtual ~Module() {}

protected:
  ICanvas *canvas = nullptr;
};
