#pragma once

#include "modules/module.hpp"
#include "common/util/better_canvas.hpp"
#include "common/models/color.hpp"
#include "modules/colors/colors_configuration.hpp"

namespace Colors
{

  class CircleAnimationRenderer : public Module<Colors::Configuration>
  {
  public:
    CircleAnimationRenderer(BetterCanvas *canvas, bool shrink = false);

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
}
