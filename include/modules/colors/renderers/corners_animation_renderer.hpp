#pragma once

#include "common/models/color.hpp"
#include "common/models/fade_data.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/renderers/renderer.hpp"
#include <vector>

namespace Colors {

class CornersAnimationRenderer : public Renderer {
public:
  CornersAnimationRenderer(BetterCanvas *canvas);

  virtual long int render() override;
  virtual void setup() override;
  virtual void teardown() override;

private:
  Color currentColor;
  int totalDiagonals;
  int loopCount;

  std::vector<FadeData> fadeData;
};
} // namespace Colors
