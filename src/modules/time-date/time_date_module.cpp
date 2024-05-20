#include "modules/time-date/time_date_module.hpp"
#include "common/util/better_canvas.hpp"
#include "common/util/pad_zeros.hpp"
#include "modules/time-date/time_date_configuration.hpp"

#include <chrono>
#include <string>

TimeDate::TimeDateModule::TimeDateModule(BetterCanvas *_canvas)
    : Module(_canvas, "time-date", "Shows the current time and date"), hours{},
      minutes{}, seconds{}, config{TimeDate::Configuration::defaults} {}

void TimeDate::TimeDateModule::setup() {
  canvas->clear();
  canvas->fontName = config.font;

  hours = "";
  minutes = "";
  seconds = "";
}

long int TimeDate::TimeDateModule::render() {
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

void TimeDate::TimeDateModule::addFlags(CLI::App *app) {
  CLI::App *cmd = app->add_subcommand(this->name, this->description);

  cmd->add_option("--font,-f", config.font,
                  "The font to use when displaying the time and date, with no "
                  "extension, it must be one of the existing fonts, for more "
                  "information check out the README.md file");
}

TimeDate::TimeDateModule::~TimeDateModule() {}
