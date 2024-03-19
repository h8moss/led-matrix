#pragma once

#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class ColorsModule : public Module<Colors::ConfigurationWithAnimation> {
public:
  ColorsModule(BetterCanvas *canvas);
  virtual ~ColorsModule();

  virtual void setup() override;
  virtual int render() override;
  virtual void teardown() override;

private:
  Module<Colors::Configuration> *renderer;
};
} // namespace Colors
