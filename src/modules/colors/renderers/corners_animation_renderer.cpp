#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <cmath>

Colors::CornersAnimationRenderer::CornersAnimationRenderer(BetterCanvas *canvas)
    : Renderer(canvas), currentColor{}, totalDiagonals{}, loopCount{},
      fullDuration{} {}

void Colors::CornersAnimationRenderer::setup() {
  canvas->clear();
  currentColor = getConfig()->getColor();
  // diagonls = x * y, we add 10 more if we are doing fading to give time for
  // the fading to actually happen
  totalDiagonals =
      canvas->getWidth() + canvas->getHeight() + (getConfig()->fading ? 10 : 0);
  loopCount = 0;
  fullDuration = getConfig()->duration + getConfig()->animationDuration;
}

long int Colors::CornersAnimationRenderer::render() {
  int progress{loopCount % (int)(fullDuration)};

  if (progress == 0) {
    canvas->fill(getConfig()->fading ? Color::black : currentColor);
    currentColor = getConfig()->getColor();
  } else if ((float)progress < getConfig()->animationDuration) {

    for (int iter{}; iter < (getConfig()->fading ? 11 : 1); iter++) {
      float fade{1.0f - (0.1f * iter)}; // TODO: If we ever make `iter` this an
                                        // argument, edit 0.1f to 1/iter
      int delta{static_cast<int>(std::floor(totalDiagonals * (float)progress /
                                            getConfig()->animationDuration)) -
                iter};

      for (int x{}; x <= delta; x++) {
        canvas->setPixel(x, delta - x - 1, currentColor * fade);
      }
    }
  }
  if (getConfig()->runOnce && progress == (int)fullDuration - 1) {
    return -1;
  }
  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
