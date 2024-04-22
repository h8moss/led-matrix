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
  // int animationProgress =
  //     loopCount %
  //     ((int)(getConfig()->animationDuration + getConfig()->duration));

  // if (getConfig()->runOnce &&
  //     animationProgress ==
  //         ((int)(getConfig()->animationDuration + getConfig()->duration)) -
  //         1) {
  //   return -1;
  // }

  // if (animationProgress == 0) {
  //   if (!getConfig()->fading)
  //     canvas->fill(currentColor);
  //   currentColor = getConfig()->getColor();
  // }

  // if ((float)animationProgress >= getConfig()->duration) {
  //   int delta{static_cast<int>(std::floor(
  //       totalDiagonals * ((float)animationProgress - getConfig()->duration) /
  //       (getConfig()->animationDuration)))};
  //   for (int x{}; x <= delta; x++) {
  //     canvas->setPixel(x, delta - x - 1, currentColor);
  //   }
  // }

  // ++loopCount;
  // return 1000;

  // States: 0. When is black, 1. When is coloring, 2. When is black again
  // States: 0. When is full of color A, 2. When is coloring with B, 3. When is
  // full of color B

  // duration and animation duration. Duration is state 0, animation duration is
  // state 1 is animadtionDur and state 2 last 0 secs

  int progress{loopCount % (int)(fullDuration)};

  if (progress == 0) {
    canvas->fill(getConfig()->fading ? Color::black : currentColor);
    currentColor = getConfig()->getColor();
  } else if (progress < getConfig()->animationDuration) {

    for (int iter{}; iter < (getConfig()->fading ? 11 : 1); iter++) {
      float fade{1.0f - (0.1f * iter)}; // BUG: If we ever make `iter` this an
                                        // argument, edit 0.1f to 1/iter
      int delta{static_cast<int>(std::floor(totalDiagonals * (float)progress /
                                            getConfig()->animationDuration)) -
                iter};

      for (int x{}; x <= delta; x++) {
        canvas->setPixel(x, delta - x - 1, currentColor * fade);
      }
    }
  } else if (progress < (int)(fullDuration)) {

    // state 1
  } else {
  }

  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
