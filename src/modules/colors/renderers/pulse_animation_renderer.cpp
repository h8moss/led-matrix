#include "modules/colors/renderers/pulse_animation_renderer.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/colors/renderers/circle_animation_renderer.hpp"

Colors::PulseAnimationRenderer::PulseAnimationRenderer(BetterCanvas *canvas)
    : Renderer(canvas), currentColor{}, animationSplits{}, loopCount{} {}

void Colors::PulseAnimationRenderer::setup() {
  canvas->clear();
  currentColor = getConfig()->getColor();

  animationSplits[0] = (int)(getConfig()->animationDuration / 2.0f);
  animationSplits[1] =
      (int)((getConfig()->animationDuration + getConfig()->duration) / 2.0f);
  animationSplits[2] =
      (int)(getConfig()->animationDuration / 2.0f + getConfig()->duration);
  animationSplits[3] =
      (int)(getConfig()->animationDuration + getConfig()->duration);

  loopCount = 0;
}

int Colors::PulseAnimationRenderer::render() {
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
    // stay black
    if (animationProgress - animationSplits[3] - 1 < 1) {
      currentColor = getConfig()->getColor(currentColor);
    }
  }

  ++loopCount;

  return 1000;
}

void Colors::PulseAnimationRenderer::teardown() { canvas->clear(); }
