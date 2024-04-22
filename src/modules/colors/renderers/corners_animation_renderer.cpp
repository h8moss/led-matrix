#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <cmath>

Colors::CornersAnimationRenderer::CornersAnimationRenderer(BetterCanvas *canvas)
    : Renderer(canvas), currentColor{}, totalDiagonals{}, loopCount{} {}

void Colors::CornersAnimationRenderer::setup() {
  canvas->clear();
  currentColor = getConfig()->getColor();
  totalDiagonals = canvas->getWidth() + canvas->getHeight() - 1;
  loopCount = 0;
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

  int progress{loopCount %
               (int)(getConfig()->duration + getConfig()->animationDuration)};

  if (progress == 0) {
    canvas->fill(getConfig()->fading ? Color::black : currentColor);
    currentColor = getConfig()->getColor();
  } else if (progress < getConfig()->duration) {
    // state 0

  } else if (progress <
             (int)(getConfig()->duration + getConfig()->animationDuration) -
                 1) {
    for (int iter{}; iter < (getConfig()->fading ? 11 : 1); iter++) {
      float fade{1.0f - (0.1f * iter)}; // BUG: If we ever make `iter` this an
                                        // argument, edit 0.2f to 1/iter
      int delta{static_cast<int>(std::floor(
                    totalDiagonals * ((float)progress - getConfig()->duration) /
                    (getConfig()->animationDuration))) -
                iter};

      for (int x{}; x <= delta; x++) {
        canvas->setPixel(x, delta - x - 1, currentColor * fade);
      }
    }
    // state 1
  } else {
    // State 2
  }

  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
