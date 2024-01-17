#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <array>
#include <iostream>

#include "models/image.hpp"
#include "visual_modules/image_visual_module.hpp"
#include "util/image_from_csv.hpp"
#include "util/read_file.hpp"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interruptReceived = false;
static void InterruptHandler(int signo) {
  interruptReceived = true;
}

static void DrawOnCanvas(Canvas *canvas) {
  try {
  canvas->Fill(0, 0, 0);

  std::string imageCSV{readFileAsText("../res/image.csv")};
  ImageVisualModule ivm{imageFromCSV(imageCSV)};

    ivm.draw(canvas);

  while (!interruptReceived) { 
  }

  canvas->Fill(0,0,0);
  } catch (const char* e) {
    std::cerr << e << '\n';
  } catch (std::string e) {
    std::cerr << e << '\n';
  } catch (std::exception e) {
    std::cerr << e.what() << '\n';
  } catch (...) {
    std::cerr << "Something went wrong" << '\n';
  }
}

int main(int argc, char *argv[]) {
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

  DrawOnCanvas(canvas);

  canvas->Clear();
  delete canvas;

  return 0;
}

/*
  From the website I should be able to:
    [ ] CRUD the playlist
    [ ] Skip to the next item on the playlist
    [ ] Pause playlist
    [ ] Set duration of each item before jump
    [ ] Set transition between item of the playlist
    [ ] Decide what happens when playlist ends (loop or jump to another playlist or turn off?)
     
  The playlist should have:
      [ ] The time
    [ ] An image (Or like a drawing made from the website)
        [ ] Slideshow
        [ ] A video (Or an animation made from the website)
        [ ] Just text, maybe scrolling, maybe the way I made the original demo (letter for letter)
          [ ] Conway's game of life
          [ ] Snake
      [ ] Just like pulses of color
              [ ] Word of the day?
              [ ] The weather?
        [ ] Rotating square
          [ ] Rotating cube?
          [ ] Sorting algorithm
        [ ] Volume bars
          [ ] Pac man?
*/