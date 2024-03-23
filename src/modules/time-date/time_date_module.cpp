#include "modules/time-date/time_date_module.hpp"
#include "common/util/better_canvas.hpp"
#include "common/util/pad_zeros.hpp"
#include "modules/time-date/time_date_configuration.hpp"

#include <chrono>
#include <string>

TimeDate::TimeDateModule::TimeDateModule(BetterCanvas *_canvas)
    : Module(_canvas, new TimeDate::Configuration()) {
  this->name = "time-date";
  this->description = "Shows the current time and date";
}

void TimeDate::TimeDateModule::setup() {

  canvas->clear();

  hours = "";
  minutes = "";
  seconds = "";
}

int TimeDate::TimeDateModule::render() {
  canvas->clear();

  auto time{std::chrono::system_clock::now()};
  auto timeT{std::chrono::system_clock::to_time_t(time)};
  auto tm{localtime(&timeT)};

  hours = padZeros(tm->tm_hour);
  minutes = padZeros(tm->tm_min);
  seconds = padZeros(tm->tm_sec);

  int weekdayNum{tm->tm_wday};
  std::string weekday{"Error on weekday"};

  if (weekdayNum == 0) {
    weekday = "sun";
  } else if (weekdayNum == 1) {
    weekday = "mon";
  } else if (weekdayNum == 2) {
    weekday = "tue";
  } else if (weekdayNum == 3) {
    weekday = "wed";
  } else if (weekdayNum == 4) {
    weekday = "thu";
  } else if (weekdayNum == 5) {
    weekday = "fri";
  } else if (weekdayNum == 6) {
    weekday = "sat";
  }

  std::string dayNum{padZeros(tm->tm_mday)};
  std::string monthNum{padZeros(tm->tm_mon + 1)};
  std::string yearNum{padZeros(tm->tm_year % 100)};

  std::string timeText{hours + ":" + minutes + ":" + seconds};

  canvas->drawText({{Color::red, timeText},
                    {Color::green, " " + weekday},
                    {Color::blue, dayNum + "/" + monthNum + "/" + yearNum}});

  return 1000000; // 1 second
}

void TimeDate::TimeDateModule::teardown() { canvas->clear(); }

TimeDate::TimeDateModule::~TimeDateModule() {}

TimeDate::Configuration *TimeDate::TimeDateModule::getConfig() const {
  return static_cast<TimeDate::Configuration *>(configuration);
}
