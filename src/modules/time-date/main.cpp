#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <chrono>
#include <string>

#include "led-matrix.h"

#include "../../common/canvas/textDrawer.hpp"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interruptReceived = false;
static void InterruptHandler(int signo) {
  interruptReceived = true;
}

static void DrawDate(Canvas *canvas) {
  canvas->Fill(0,0,0);

  std::string hours{};
  std::string minutes{};
  std::string seconds{};

  TextDrawer td{canvas};

  while (!interruptReceived) {
    canvas->Fill(0,0,0);

    auto time{std::chrono::system_clock::now()};
    auto timeT{std::chrono::system_clock::to_time_t(time)};
    auto tm{localtime(&timeT)};

    hours = std::to_string(tm->tm_hour);
    minutes = std::to_string(tm->tm_min);
    seconds = std::to_string(tm->tm_sec);
    if (hours.length() == 1) hours = '0' + hours;
    if (minutes.length() == 1) hours = '0' + minutes;
    if (seconds.length() == 1) hours = '0' + seconds;

    int weekdayNum{tm->tm_wday};
    std::string weekday{"error aaa"};
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

    int dayNum{tm->tm_mday};
    int monthNum{tm->tm_mon + 1};
    int yearNum{tm->tm_year % 100};

    td.drawText(hours + ":" + minutes + ":" + seconds, 2, 2, Color::red);
    td.drawText(weekday, 2, 10, Color::green);
    td.drawText(std::to_string(dayNum) + " " + std::to_string(monthNum) + " " + std::to_string(yearNum), 2, 20, Color::blue);

    usleep(1000* 1000); // Sleep 1 second
  }

}

int main(int argc, char** argv) {
  // Show date, day of week, time, weather?
  try {

    RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = false;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
      return 1;

    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    DrawDate(canvas);

    canvas->Clear();
    delete canvas;
  } catch (const char* err) {
    std::cerr << err << std::endl;
  } catch (const std::string err) {
    std::cerr << err << std::endl;
  } catch (const std::exception err) {
    std::cerr << "Something went wrong!" << '\n';
    std::cerr << err.what() << std::endl;
  }

  return 0;
}
