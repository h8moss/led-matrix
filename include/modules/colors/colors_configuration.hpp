#pragma once
#include "common/models/color.hpp"
#include "modules/module_configuration.hpp"

#include <vector>

namespace Colors {

enum ColorGenerationStrategy { random, trueRandom, specific };

enum Animation { pulse, corners, shrink, grow };

class Configuration : public ModuleConfiguration {
public:
  Configuration();

  virtual const char *getHelp() const override;
  virtual void parseArguments(char **argv, int argc) override;
  virtual void parseData(std::string data) override;

  ColorGenerationStrategy colorGenerationStrategy;
  std::vector<Color> colors;
  float duration;
  float animationDuration;

  Color getColor(Color lastColor = Color::black) const;

  ~Configuration();
};

class ConfigurationWithAnimation : public Configuration {
public:
  ConfigurationWithAnimation();

  virtual void parseArguments(char **argv, int argc) override;
  virtual void parseData(std::string data) override;

  Animation animation;

  ~ConfigurationWithAnimation();
};
} // namespace Colors
