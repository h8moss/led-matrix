#include "modules/colors/colors_module.hpp"
#include "common/util/arg_parser.hpp"
#include "common/util/enum_checked_transformer.hpp"
#include "modules/colors/colors_configuration.hpp"
#include "modules/colors/renderers/circle_animation_renderer.hpp"
#include "modules/colors/renderers/corners_animation_renderer.hpp"
#include "modules/colors/renderers/pulse_animation_renderer.hpp"
#include "modules/module.hpp"

#include "CLI/CLI.hpp"
#include <stdexcept>
#include <string>

Colors::ColorsModule::ColorsModule(ICanvas *canvas)
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

Colors::ColorsModule::~ColorsModule() {
  delete renderer;
  renderer = nullptr;
}

void Colors::ColorsModule::addFlags(CLI::App *app) {
  auto module = app->add_subcommand(this->name, this->description);

  auto colorOpt = module->add_option(
      "--color,-c", config.colors, "A color you want the animation to contain");

  module->add_option(
      "--duration,-d", config.duration,
      "The amount of time, in miliseconds, a color should remain on screen");

  module
      ->add_option("--animation, -a", config.animation, "The animation to show")
      ->transform(EnumCheckedTransformer(
          {{"pulse", Colors::Animation::pulse},
           {"corners", Colors::Animation::corners},
           {"grow", Colors::Animation::grow},
           {"shrink", Colors::Animation::shrink}},
          {{Colors::Animation::pulse, "A simple pulse animation"},
           {Colors::Animation::corners,
            "Colors rush from one corner to the other"},
           {Colors::Animation::grow, "A circle of color grows from the center"},
           {Colors::Animation::shrink,
            "A circle of color shrinks into the center"}}));

  module->add_option("--animation-duration,--ad", config.animationDuration,
                     "The amount of time, in miliseconds, tha transition "
                     "between colors lasts");

  module
      ->add_flag("--true-random-colors", config.useTrueRandomColors,
                 "Pass this flag if you want the colors to be fully random, "
                 "even when the colors may be ugly")
      ->excludes(colorOpt);

  module->add_flag("--fade,-f", config.fading,
                   "Make the colors fade to black as they're drawn (does "
                   "nothing for pulse animation)");

  module->add_flag("--once", config.runOnce,
                   "The animation runs once and then it exits");
}

void Colors::ColorsModule::readArguments(
    std::map<std::string, std::vector<std::string>> map) {
  config = Colors::ConfigurationWithAnimation::defaults;

  if (map.count("run-once")) {
    config.runOnce = ArgParser::ensureBoolean(map, "run-once");
  }
  if (map.count("animation")) {
    std::string value = ArgParser::ensureSingle(map, "animation");
    if (!ConfigurationWithAnimation::animationMap.count(value)) {
      throw "Unrecognized animation: " + value;
    }
    config.animation = ConfigurationWithAnimation::animationMap[value];
  }
  if (map.count("color")) {
    config.colors = {};
    for (auto c : map["color"]) {
      config.colors.push_back(Color::fromHex(c));
    }
  }
  if (map.count("fade")) {
    config.fading = ArgParser::ensureBoolean(map, "fade");
  }
  if (map.count("duration")) {
    std::string value = ArgParser::ensureSingle(map, "duration");
    try {
      config.duration = std::stof(value);
    } catch (std::invalid_argument e) {
      throw "Could not understand the value of duration";
    }
  }
  if (map.count("animation-duration")) {
    std::string value = ArgParser::ensureSingle(map, "animation-duration");
    try {
      config.animationDuration = std::stof(value);
    } catch (std::invalid_argument e) {
      throw "Could not understand the value of animation-duration";
    }
  }
  if (map.count("true-random-colors")) {
    config.useTrueRandomColors =
        ArgParser::ensureBoolean(map, "true-random-colors");
  }
}
