#include "modules/colors/colors_module.hpp"
#include "common/util/better_canvas.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/colors/renderers/circle_animation_renderer.hpp"
#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "modules/colors/renderers/pulse_animation_renderer.hpp"
#include "modules/module.hpp"

#include "CLI/CLI.hpp"

Colors::ColorsModule::ColorsModule(BetterCanvas *canvas)
    : Module(canvas, "colors", "Shows simple color animations"),
      config{Colors::ConfigurationWithAnimation::defaults}, renderer{} {}

void Colors::ColorsModule::setup() {
  if (config.animation == Animation::corners)
    renderer = new CornersAnimationRenderer(canvas, config);
  else if (config.animation == Animation::grow)
    renderer = new CircleAnimationRenderer(canvas, config);
  else if (config.animation == Animation::shrink)
    renderer = new CircleAnimationRenderer(canvas, config, true);
  else if (config.animation == Animation::pulse)
    renderer = new PulseAnimationRenderer(canvas, config);
  else
    throw "Unknown Animation";

  renderer->setup();
}

long int Colors::ColorsModule::render() { return renderer->render(); }

void Colors::ColorsModule::teardown() { renderer->teardown(); }

Colors::ColorsModule::~ColorsModule() { delete renderer; }

void Colors::ColorsModule::addFlags(CLI::App *app) {
  auto module = app->add_subcommand(this->name, this->description);

  dLog("adding color opt");
  auto colorOpt = module->add_option(
      "--color,-c", config.colors, "A color you want the animation to contain");

  dLog("adding duration opt");
  module->add_option(
      "--duration,-d", config.duration,
      "The amount of time, in miliseconds, a color should remain on screen");

  dLog("adding animmation opt");
  module
      ->add_option("--animation, -a", config.animation, "The animation to show")
      ->transform(CLI::CheckedTransformer(
          Colors::ConfigurationWithAnimation::animationMap, CLI::ignore_case));

  dLog("adding animmation duration opt");
  module->add_option("--animation-duration,--ad", config.animationDuration,
                     "The amount of time, in miliseconds, tha transition "
                     "between colors lasts");

  dLog("adding true random colors opt");
  module
      ->add_flag("--true-random-colors", config.useTrueRandomColors,
                 "Pass this flag if you want the colors to be fully random, "
                 "even when the colors may be ugly")
      ->excludes(colorOpt);

  dLog("adding fade opt");
  module->add_flag("--fade,-f", config.fading,
                   "Make the colors fade to black as they're drawn (does "
                   "nothing for pulse animation)");

  dLog("adding once opt");
  module->add_flag("--once", config.runOnce,
                   "The animation runs once and then it exits");
}
