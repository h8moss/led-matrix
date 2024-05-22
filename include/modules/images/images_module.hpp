#pragma once

#include "modules/images/images_configuration.hpp"
#include "modules/module.hpp"

namespace Images {
class ImagesModule : public Module {
public:
  ImagesModule(BetterCanvas *canvas);
  virtual ~ImagesModule();

  virtual void setup() override;
  virtual long int render() override;
  virtual void teardown() override;

  Images::Configuration *getConfig() const;

  virtual void createConfiguration() override;
};
} // namespace Images
