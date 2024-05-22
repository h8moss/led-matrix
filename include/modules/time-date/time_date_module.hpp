#pragma once
#include "common/canvas/icanvas.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_configuration.hpp"

#include <string>

namespace TimeDate {
class TimeDateModule : public Module {
public:
  TimeDateModule(ICanvas *_canvas);

  void setup() override;
  long int render() override;
  void teardown() override;

  void addFlags(CLI::App *app) override;
  void
  readArguments(std::map<std::string, std::vector<std::string>> args) override;

  ~TimeDateModule();

protected:
  std::string hours;
  std::string minutes;
  std::string seconds;

  TimeDate::Configuration config;
};
} // namespace TimeDate
