#pragma once

#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class Renderer : public Module {
public:
  Renderer(BetterCanvas *canvas, Colors::Configuration config);

  void addFlags(CLI::App *app) override;

protected:
  Colors::Configuration config;
};

} // namespace Colors
