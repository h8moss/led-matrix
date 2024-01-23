#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <chrono>

#include "led-matrix.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interruptReceived = false;
static void InterruptHandler(int signo) {
  interruptReceived = true;
}

static void DrawDate(Canvas *canvas) {
  canvas->Fill(0,0,0);

  int hours{};
  int minutes{};
  int seconds{};

  while (!interruptReceived) {
    canvas->Fill(0,0,0);

    auto time{std::chrono::system_clock::now()};
    auto timeT{std::chrono::system_clock::to_time_t(time)};
    auto tm{localtime(&timeT)};

    std::cout << tm->tm_hour << ':' << tm->tm_min << ":" << tm->tm_sec << '\n';

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