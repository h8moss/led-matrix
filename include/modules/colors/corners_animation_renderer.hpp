#pragma once

#include "modules/module.hpp"
#include "common/util/better_canvas.hpp"
#include "common/models/color.hpp"
#include "modules/colors/colors_configuration.hpp"

namespace Colors
{

  class CornersAnimationRenderer : public Module<Colors::Configuration>
  {
  public:
    CornersAnimationRenderer(BetterCanvas *canvas);

    virtual int render() override;
    virtual void setup() override;
    virtual void teardown() override;

  private:
    Color currentColor;
    int totalDiagonals;
    int loopCount;
  };
}
