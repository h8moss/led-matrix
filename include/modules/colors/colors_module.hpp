#pragma once

#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {
class ColorsModule : public Module {
public:
  ColorsModule(BetterCanvas *canvas);
  virtual ~ColorsModule();

  virtual void setup() override;
  virtual long int render() override;
  virtual void teardown() override;

  Colors::ConfigurationWithAnimation *getConfig() const;

  virtual void createConfiguration() override;

private:
  Module *renderer;
};
} // namespace Colors
