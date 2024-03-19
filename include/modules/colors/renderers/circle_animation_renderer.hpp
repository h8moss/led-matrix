#pragma once

#include "common/models/color.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

namespace Colors {

class CircleAnimationRenderer : public Module<Colors::Configuration> {
public:
  CircleAnimationRenderer(BetterCanvas *canvas, bool _shrink = false);
  virtual ~CircleAnimationRenderer();

  virtual int render() override;
  virtual void setup() override;
  virtual void teardown() override;

private:
  int radius;
  int currentRadius;
  int centerX;
  int centerY;
  Color color;
  int loopCount;

  bool shrink;
};
} // namespace Colors
