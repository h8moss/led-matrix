#pragma once

#include "common/canvas/icanvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class ColorsModule : public Module {
public:
  ColorsModule(ICanvas *canvas);
  ~ColorsModule();

  void setup() override;
  long int render() override;
  void teardown() override;

  void addFlags(CLI::App *app) override;
  void
  readArguments(std::map<std::string, std::vector<std::string>> args) override;

private:
  Module *renderer;

  Colors::ConfigurationWithAnimation config;
};
} // namespace Colors
