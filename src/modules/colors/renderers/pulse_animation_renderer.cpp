#include "modules/colors/renderers/pulse_animation_renderer.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"

Colors::PulseAnimationRenderer::PulseAnimationRenderer(
    BetterCanvas *canvas, Colors::Configuration config)
    : Renderer(canvas, config), currentColor{}, animationSplits{}, loopCount{} {
}

void Colors::PulseAnimationRenderer::setup() {
  canvas->clear();
  currentColor = config.getColor();

  animationSplits[0] = (int)(config.animationDuration / 2.0f);
  animationSplits[1] =
      (int)((config.animationDuration + config.duration) / 2.0f);
  animationSplits[2] = (int)(config.animationDuration / 2.0f + config.duration);
  animationSplits[3] = (int)(config.animationDuration + config.duration);

  loopCount = 0;
}

long int Colors::PulseAnimationRenderer::render() {
  int animationProgress = loopCount % (int)animationSplits[3];
  if (animationProgress < animationSplits[0]) {
    // animate color in
    float progress{(float)animationProgress / animationSplits[0]};
    canvas->fill(currentColor * progress);
  } else if (animationProgress < animationSplits[1]) {
  } else if (animationProgress < animationSplits[2]) {
    float progress{(float)(-animationProgress + animationSplits[2]) /
                   (float)(animationSplits[2] - animationSplits[1])};
    canvas->fill(currentColor * progress);
  } else if (animationProgress < animationSplits[3]) {
    if (config.runOnce)
      return -1;

    // stay black
    if (animationProgress - animationSplits[3] - 1 < 1) {
      dLog(animationProgress - animationSplits[3] - 1 < 1);
      currentColor = config.getColor(currentColor);
    }
  }

  ++loopCount;

  return 1000;
}

void Colors::PulseAnimationRenderer::teardown() { canvas->clear(); }
