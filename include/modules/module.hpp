#pragma once
#include "common/util/better_canvas.hpp"

#include <string>

template <typename TConfig> class Module {
public:
  Module(BetterCanvas *_canvas) : configuration{}, canvas{_canvas} {}

  std::string name;
  std::string description;

  virtual void setup() = 0;
  virtual int render() = 0;
  virtual void teardown() = 0;
  TConfig configuration;

  virtual ~Module() { delete canvas; }

protected:
  BetterCanvas *canvas = nullptr;
};
