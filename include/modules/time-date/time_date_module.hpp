#pragma once
#include "common/util/better_canvas.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_configuration.hpp"

#include <string>

namespace TimeDate {
class TimeDateModule : public Module {
public:
  TimeDateModule(BetterCanvas *_canvas);

  virtual void setup() override;
  virtual long int render() override;
  virtual void teardown() override;

  TimeDate::Configuration *getConfig() const;

  virtual void createConfiguration() override;

  virtual ~TimeDateModule();

protected:
  std::string hours;
  std::string minutes;
  std::string seconds;
};
} // namespace TimeDate
