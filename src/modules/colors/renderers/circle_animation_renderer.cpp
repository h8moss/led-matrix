#include "modules/colors/renderers/circle_animation_renderer.hpp"
#include "common/canvas/icanvas.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"

#include <algorithm>
#include <cmath>

Colors::CircleAnimationRenderer::CircleAnimationRenderer(
    ICanvas *canvas, Colors::Configuration config, bool _shrink)
    : Renderer(canvas, config), radius{}, currentRadius{}, centerX{}, centerY{},
      color{}, loopCount{}, shrink{_shrink} {}

void Colors::CircleAnimationRenderer::setup()
{
  canvas->clear();
  radius = (int)std::sqrt(canvas->getHeight() * canvas->getHeight() +
                          canvas->getWidth() * canvas->getWidth()) +
           1;
  centerX = canvas->getWidth() / 2;
  centerY = canvas->getHeight() / 2;

  currentRadius = 0;
  loopCount = 0;

  color = config.getColor();
}

long int Colors::CircleAnimationRenderer::render()
{
  int progress{loopCount % (int)(config.animationDuration + config.duration)};
  if (progress == 0)
  {
    canvas->fill(color);
    color = config.getColor();
  }

  if (config.runOnce &&
      progress == (int)(config.animationDuration + config.duration) - 1)
  {
    return -1;
  }

  if ((float)progress <= config.animationDuration)
  {
    float percent{(float)progress / config.animationDuration};
    if (shrink)
      percent = 1.0f - percent;
    int nextRadius{(int)(radius * percent)};
    if (nextRadius != currentRadius)
    {
      currentRadius = nextRadius;
      for (int i{}; i <= (config.fading ? 10 : 0); i++)
      {
        // TODO: Test this works
        float fade{
            std::max(
                0.0f,
                std::min(1.0f,
                         (1.0f - (float)i / 10.0f)))};
        dLog(fade);
        dLog(1.0f - (float)i / 10.0f);
        dLog(i);
        canvas->drawCircle(centerX, centerY, currentRadius + i * (shrink ? 1 : -1),
                           color * fade, true);
      }
    }
  }

  ++loopCount;
  return 1000;
}

void Colors::CircleAnimationRenderer::teardown() { canvas->clear(); }
