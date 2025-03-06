#pragma once

#include "common/canvas/icanvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class Renderer : public Module {
public:
  Renderer(ICanvas *canvas, Colors::Configuration config);

  void addFlags(CLI::App *app) override;
  void
  readArguments(std::map<std::string, std::vector<std::string>> args) override;

protected:
  Colors::Configuration config;
};

} // namespace Colors
