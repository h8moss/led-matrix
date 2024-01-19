#include <iostream>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <array>

#include "colors_configuration.hpp"
#include "parse_arguments.hpp"

#include "led-matrix.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interruptReceived = false;
static void InterruptHandler(int signo) {
  interruptReceived = true;
}

using namespace ColorsModule;

static void DrawOnCanvas(Canvas *canvas, ColorsConfiguration config) {
  canvas->Fill(0,0,0);

  Color currentColor{config.getColor()};

  int loopCount{};
  while (!interruptReceived) {
    int animationProgress = loopCount % 400;   
    if (animationProgress < 100) {
      // animate color in
      float colorProgress{(float)animationProgress/100.0f};
      canvas->Fill(currentColor.r * colorProgress, currentColor.g * colorProgress, currentColor.b * colorProgress);
    } else if (animationProgress < 200) {
      // canvas->Fill(255,0,0);
    } else if (animationProgress < 300) {
      float colorProgress{(float)(-animationProgress + 300)/100.0f};
      canvas->Fill(currentColor.r * colorProgress, currentColor.g * colorProgress, currentColor.b * colorProgress);
    } else if (animationProgress < 400) {
      // stay black

      if (animationProgress == 301) {
        currentColor = config.getColor();
      }
    }

    ++loopCount;
    usleep(1000); // sleep for a ms
  }

  canvas->Fill(0,0,0);
}

int main(int argc, char** argv) {
  try {
    ColorsConfiguration config{parseArguments(argc, argv)};
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

    DrawOnCanvas(canvas, config);

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