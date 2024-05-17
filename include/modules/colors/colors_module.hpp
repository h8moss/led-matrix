#pragma once

#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class ColorsModule : public Module {
public:
  ColorsModule(BetterCanvas *canvas);
  ~ColorsModule();

  void setup() override;
  long int render() override;
  void teardown() override;

  void addFlags(CLI::App *app) override;

private:
  Module *renderer;

  Colors::ConfigurationWithAnimation config;
};
} // namespace Colors
