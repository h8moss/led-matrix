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

static void DrawShrink(Canvas *canvas, ColorsConfiguration config) {
  canvas->Fill(0,255,0);

  int radius{(int)std::sqrt(
    canvas->height() * canvas->height() 
    + canvas->width() * canvas->width()
  )+1};

  int currentRadius{};

  int centerX{canvas->width()/2};
  int centerY{canvas->height()/2};

  int loopCount{};
  while (!interruptReceived) {
    int animationProgress{loopCount % (int)(config.animationDuration + config.duration)};

    if (animationProgress >= config.duration) {
      float percent{1.0f-(((float)animationProgress-config.duration) / config.animationDuration)};
      int nextRadius{(int)(radius*percent)};
      if (nextRadius != currentRadius) {
        for (int x{}; x<canvas->width();x++) {
          for (int y{}; y<canvas->height(); y++) {
            int xCentered{x-centerX};
            int yCentered{y-centerY};
            int distanceSquared{xCentered * xCentered + yCentered * yCentered};
            if (distanceSquared > currentRadius * currentRadius) {
              canvas->SetPixel(x, y, 255, 0, 0);
            }
          }
        }
      }
      // int currentRadius{10};

      // int t1{currentRadius / 16};
      // int x{currentRadius};
      // int y{};
      // while (x >= y) {
      //   canvas->SetPixel(centerX+x, centerY+y, 255, 0, 0);
      //   canvas->SetPixel(centerX-x, centerY+y, 255, 0, 0);
      //   canvas->SetPixel(centerX+x, centerY-y, 255, 0, 0);
      //   canvas->SetPixel(centerX-x, centerY-y, 255, 0, 0);
      //   ++y;
      //   t1 += y;
      //   int t2{t1-x};
      //   if (t2 >= 0) {
      //     t1 = t2;
      //     x--;
      //   }
      // }

    }

    ++loopCount;
    usleep(1000);
  }
}

static void DrawCorners(Canvas *canvas, ColorsConfiguration config) {
  canvas->Fill(0,0,0);

  Color currentColor{config.getColor()};
  int totalDiagonals{127}; // 64 rows * 64 columns - 1 shared diagonal
  // TODO: If we want this code to run on any size, we need to make this dynamic

  int loopCount{};
  while (!interruptReceived) {
    int animationProgress = loopCount % ((int)(config.animationDuration + config.duration));

    if (animationProgress == 0) {
      canvas->Fill(currentColor.r, currentColor.g, currentColor.b);
      currentColor = config.getColor();
    }

    if (animationProgress >= config.duration) {
      int delta{std::floor(totalDiagonals*((float)animationProgress-config.duration)/(config.animationDuration))};
      for (int x{}; x<=delta; x++) {
        canvas->SetPixel(x, delta-x-1, currentColor.r, currentColor.g, currentColor.b);
      }
    }     

    ++loopCount;
    usleep(1000);
  }

  canvas->Fill(0,0,0);
}

static void DrawPulse(Canvas *canvas, ColorsConfiguration config) {
  canvas->Fill(0,0,0);

  Color currentColor{config.getColor()};

  int animationSplit1{config.animationDuration / 2.0f};
  int animationSplit2{(config.animationDuration + config.duration) / 2.0f};
  int animationSplit3{config.animationDuration / 2.0f + config.duration};
  int animationSplit4{config.animationDuration + config.duration};

  int loopCount{};
  while (!interruptReceived) {
    int animationProgress = loopCount % (int)animationSplit4;
    if (animationProgress < animationSplit1) {
      // animate color in
      float progress{(float)animationProgress/animationSplit1};
      canvas->Fill(currentColor.r * progress, currentColor.g * progress, currentColor.b * progress);
    } else if (animationProgress < animationSplit2) {
      
    } else if (animationProgress < animationSplit3) {
      float progress{(float)(-animationProgress + animationSplit3)/(float)(animationSplit3-animationSplit2)};
      canvas->Fill(currentColor.r * progress, currentColor.g * progress, currentColor.b * progress);
    } else if (animationProgress < animationSplit4) {
      // stay black
      if (animationProgress - animationSplit4-1 < 1) {
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

    if (config.showHelp) {
      std::cout << "Program to show animations of colors on the full screen" << '\n';
      std::cout << "Usage: sudo colors.out [options]" << "\n\n";
      std::cout << "Options:" << '\n';
      std::cout << "--colors <COLORS>, -c <COLORS>" << '\n';
      std::cout << "\tPass a list of colors you want the screen to cycle through" << '\n';
      std::cout << "--duration <ms>, -d <ms>" << '\n';
      std::cout << "\tThe amount of time, in miliseconds a color should remain on the screen (default 5000)" << '\n';
      std::cout << "--animation <ANIMATION>, -a <ANIMATION>" << '\n';
      std::cout << "\tThe animation to show, should be one of the following values:" << '\n';
      std::cout << "\t\tpulse (default) - A color pulses on the screen" << '\n';
      std::cout << "\t\tcorners - A color moves from one corner to the opposite" << '\n';
      std::cout << "\t\tshrink - The last color shrinks to the center of the screen" << '\n';
      std::cout << "\t\tgrow - The next color grows from the center of the screen" << '\n';
      std::cout << "--animation-duration <ms>, --ad <ms>" << '\n';
      std::cout << "\tThe amount of time, in miliseconds the transition between colors should last (default 1000)";
      std::cout << "--true-random-colors, -r" << '\n';
      std::cout << "\tNormally, the screen only shows fully saturated, medium lightness colors, passing this flag makes the screen show truly randomized colors" << '\n';
    
      return 0;
    }

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

    if (config.animation == Animation::pulse)
      DrawPulse(canvas, config);
    else if (config.animation == Animation::corners)
      DrawCorners(canvas, config);
    else if (config.animation == Animation::shrink)
      DrawShrink(canvas, config);

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