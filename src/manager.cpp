#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "common/canvas/better_canvas.hpp"
#include "common/canvas/debug_canvas.hpp"
#include "common/canvas/icanvas.hpp"
#include "common/util/arg_parser.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_module.hpp"
#include "modules/game-of-life/game_of_life_module.hpp"
#include "modules/images/images_module.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_module.hpp"

#include "Magick++.h"
#include "led-matrix.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);
  ICanvas *canvas;

  try {

#ifdef DEVLAPTOP

    canvas = new DebugCanvas();

#else

    rgb_matrix::RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = false;
    canvas = new BetterCanvas(argc, argv, defaults);

#endif
    std::vector<Module *> modules{
        new Colors::ColorsModule(canvas), new GameOfLife::GOLModule(canvas),
        new TimeDate::TimeDateModule(canvas), new Images::ImagesModule(canvas)};

    long int timeCounter{};

    if (argc < 2) {
      cout << "USAGE: sudo led-matrix-manager <FIFO>" << endl;
    }

    Module *module{nullptr};

    const char *fifoPath{argv[1]};

    int fd{open(fifoPath, O_RDONLY | O_NDELAY)};
    long number{};
    char s[50];

    bool shouldExit{false};

    do {
      if (timeCounter >= 1000) { // Only check commands every second
        number = read(fd, s, 50);
        timeCounter = 0;

      } else {
        number = 0;
      }
      dLog("number: " + std::to_string(number));
      if (number > 0) {
        // Received instructions
        dLog("Received instructions: ");
        s[number] = '\0';
        std::string instruction{s};
        ArgParser parser{ArgParser()};
        parser.parse(instruction);

        if (parser.name == "die") {
          dLog("Received DEATH");
          break;
        } else if (parser.name == "off") {
          module->teardown();
          module = nullptr;
          continue;
        }

        for (auto mod : modules) {
          dLog("CHECKING " + mod->name);
          if (parser.name == mod->name) {
            dLog("Initiating " + mod->name);
            if (module != nullptr) {
              module->teardown();
            }
            module = mod;
            module->readArguments(parser.values);
            module->setup();
            break;
          }
        }
      } else {
        // Normal loop
        if (module != nullptr) {
          long int sleepTime{module->render()};
          if (sleepTime < 0) {
            module->teardown();
            module = nullptr;
            continue;
          }
          timeCounter += sleepTime / 1000;
          if (sleepTime > 1000000) {
            sleep(sleepTime / 1000000);
            sleepTime = sleepTime % 1000000;
          }
          if (sleepTime > 0) {
            usleep(sleepTime);
          }
        } else {
          sleep(1);
          timeCounter += 1000;
        }
      }
    } while (!shouldExit);

    if (module != nullptr) {
      module->teardown();
      module = nullptr;
    }

    for (auto mod : modules) {
      delete mod;
    }

  } catch (const char *err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (const std::string err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (const std::exception err) {
    std::cerr << "Something went wrong!" << '\n';
    std::cerr << err.what() << std::endl;
  }

  return 0;
}
