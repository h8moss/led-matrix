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

  float halfAnimationDuration{config.animationDuration/2.0f};
  float halfDuration{config.duration/2.0f};
  float fullDuration{config.duration + config.animationDuration};

  int loopCount{};
  while (!interruptReceived) {
    int animationProgress = loopCount % (int)fullDuration;
    if (animationProgress < halfAnimationDuration) {
      // animate color in
      float progress{(float)animationProgress/halfAnimationDuration};
      canvas->Fill(currentColor.r * progress, currentColor.g * progress, currentColor.b * progress);
    } else if (animationProgress < halfAnimationDuration + halfDuration) {
      
    } else if (animationProgress < config.animationDuration + halfDuration) {
      float progress{(-((float)animationProgress-halfDuration)/halfAnimationDuration)};
      canvas->Fill(currentColor.r * progress, currentColor.g * progress, currentColor.b * progress);
    } else if (animationProgress < fullDuration) {
      // stay black
      if (animationProgress - fullDuration-1 < 1) {
        currentColor = config.getColor(currentColor);
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