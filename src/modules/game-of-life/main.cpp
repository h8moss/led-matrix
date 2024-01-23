#include "parse_arguments.hpp"
#include "game_of_life_configuration.hpp"

#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include <signal.h>
#include <unistd.h>

#include "led-matrix.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

volatile bool interruptReceived = false;
static void InterruptHandler(int signo) {
  interruptReceived = true;
}

using namespace GameOfLifeModule;

static int CountNeighbors(bool** board, int x, int y, int width, int height) {
  int count{};

  for (int xDelta{-1}; xDelta <= 1; xDelta++) {
    for (int yDelta{-1}; yDelta <= 1; yDelta++) {
      if (xDelta == yDelta && xDelta == 0) continue;
      int currentX{x + xDelta};
      int currentY{y + yDelta};

      if (currentX < 0 || currentX >= width) continue;
      if (currentY < 0 || currentY >= height) continue;

      count += board[currentX][currentY];
    }
  }

  return count;
}

static void DrawGame(Canvas *canvas, GameOfLifeConfiguration config) {
  canvas->Fill(0,0,0);

  int w{canvas->width()};
  int h{canvas->height()};

  bool **board{new bool*[w]};
  bool **boardChanges{new bool*[w]};

  for (int x{}; x<w; x++) {
    board[x] = new bool[h]{};
    boardChanges[x] = new bool[h]{};
    for (int y{}; y<h; y++) {
      bool value{rand() & 1};
      board[x][y] = value;

      canvas->SetPixel(x, y, config.color.r * value, config.color.g * value, config.color.b * value);
    }
  }

  while (!interruptReceived) {
    for (int x{}; x<w; x++) {
      for (int y{}; y<h; y++) {
        bool value{board[x][y]};

        int aliveNeighbors{CountNeighbors(board, x, y, w, h)};

        if (value && (aliveNeighbors < 2 || aliveNeighbors > 3)) {
          boardChanges[x][y] = true;
        } else if (!value && aliveNeighbors == 3) {
          boardChanges[x][y] = true;
        }
      }
    }

    for (int x{}; x<w; x++) {
      for (int y{}; y<h; y++) {
        if (boardChanges[x][y]) {
          board[x][y] = !board[x][y];
          Color c{board[x][y] ? config.color : Color::black};
          canvas->SetPixel(x, y, c.r, c.g, c.b);
          boardChanges[x][y] = false;
        }
      }
    }

    usleep(config.duration * 1000);
  }

  canvas->Fill(0,0,0);
}

int main(int argc, char** argv) {
  srand(time(NULL));

  try {
    GameOfLifeConfiguration config{parseArguments(argc, argv)};

    if (config.showHelp) {
      std::cout << "Program to show Conway's game of life on screen" << '\n';
      std::cout << "Usage: sudo game_of_life.out [options]" << "\n\n";
      std::cout << "Options:" << '\n';
      std::cout << "--color <COLOR>, -c <COLORS>" << '\n';
      std::cout << "\tPass the color you want the game to be" << '\n';
      std::cout << "--duration <ms>, -d <ms>" << '\n';
      std::cout << "\tThe amount of time, in miliseconds a round lasts (default 100)" << '\n';

      return 0;
    }

    if (config.generateColor) {
      config.color = Color::fromHSL(rand() % 360, 1.0f, 0.5f);
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

    DrawGame(canvas, config);

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