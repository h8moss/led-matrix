#include "modules/colors/colors_module.hpp"
#include "common/util/better_canvas.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/module.hpp"

#include "modules/colors/renderers/circle_animation_renderer.hpp"
#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "modules/colors/renderers/pulse_animation_renderer.hpp"

Colors::ColorsModule::ColorsModule(BetterCanvas *canvas)
    : Module(canvas, new ConfigurationWithAnimation()) {}

void Colors::ColorsModule::setup() {
  auto conf{static_cast<Colors::ConfigurationWithAnimation *>(configuration)};
  if (conf->animation == Animation::corners)
    renderer = new CornersAnimationRenderer(canvas);
  else if (conf->animation == Animation::grow)
    renderer = new CircleAnimationRenderer(canvas);
  else if (conf->animation == Animation::shrink)
    renderer = new CircleAnimationRenderer(canvas, true);
  else if (conf->animation == Animation::pulse)
    renderer = new PulseAnimationRenderer(canvas);
  else
    throw "Unknown Animation";

  renderer->configuration = this->configuration;
  renderer->setup();
}

int Colors::ColorsModule::render() { return renderer->render(); }

void Colors::ColorsModule::teardown() { renderer->teardown(); }

Colors::ColorsModule::~ColorsModule() { delete renderer; }
