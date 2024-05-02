#pragma once

#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class Renderer : public Module {
public:
  Renderer(BetterCanvas *canvas);

  Colors::Configuration *getConfig() const;

  virtual void createConfiguration() override;
};

} // namespace Colors
