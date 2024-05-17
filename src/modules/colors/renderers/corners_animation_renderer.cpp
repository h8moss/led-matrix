#include "modules/colors/renderers/corners_animation_renderer.hpp"

Colors::CornersAnimationRenderer::CornersAnimationRenderer(
    BetterCanvas *canvas, Colors::Configuration config)
    : Renderer(canvas, config), currentColor{}, totalDiagonals{}, loopCount{},
      fullDuration{} {}

void Colors::CornersAnimationRenderer::setup() {
  canvas->clear();
  currentColor = config.getColor();
  // diagonls = x * y, we add 10 more if we are doing fading to give time for
  // the fading to actually happen
  totalDiagonals =
      canvas->getWidth() + canvas->getHeight() + (config.fading ? 10 : 0);
  loopCount = 0;
  fullDuration = config.duration + config.animationDuration;
}

long int Colors::CornersAnimationRenderer::render() {
  int progress{loopCount % (int)(fullDuration)};

  if (progress == 0) {
    canvas->fill(config.fading ? Color::black : currentColor);
    currentColor = config.getColor();
  } else if ((float)progress < config.animationDuration) {

    for (int iter{}; iter < (config.fading ? 11 : 1); iter++) {
      float fade{1.0f - (0.1f * iter)}; // TODO: If we ever make `iter` an
                                        // argument, edit 0.1f to 1.0f/iter
      int delta{static_cast<int>(std::floor(totalDiagonals * (float)progress /
                                            config.animationDuration)) -
                iter};

      for (int x{}; x <= delta; x++) {
        canvas->setPixel(x, delta - x - 1, currentColor * fade);
      }
    }
  }
  if (config.runOnce && progress == (int)fullDuration - 1) {
    return -1;
  }
  ++loopCount;
  return 1000;
}

void Colors::CornersAnimationRenderer::teardown() { canvas->clear(); }
