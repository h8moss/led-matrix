#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "common/util/better_canvas.hpp"
#include "common/util/debug_log.hpp"
#include "modules/colors/colors_module.hpp"
#include "modules/game-of-life/game_of_life_module.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_module.hpp"

#include "led-matrix.h"

using std::cout;
using std::endl;

int main(int argc, char **argv) {
  try {
    rgb_matrix::RGBMatrix::Options defaults;
    defaults.hardware_mapping = "regular";
    defaults.rows = 64;
    defaults.cols = 64;
    defaults.chain_length = 1;
    defaults.parallel = 1;
    defaults.show_refresh_rate = false;
    BetterCanvas *canvas = new BetterCanvas(argc, argv, defaults);

    std::vector<Module *> modules{
        new Colors::ColorsModule(canvas),
        new GameOfLife::GOLModule(canvas),
        new TimeDate::TimeDateModule(canvas),
    };

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
      number = read(fd, s, 50);
      dLog("number: " + std::to_string(number));
      if (number > 0) {
        // Received instructions
        dLog("Received instructions: ");
        s[number] = '\0';
        std::string instruction{s};
        dLog(s);
        dLog("Instruction \"" + instruction + "\" == die? " + instruction ==
             "die");
        if (instruction == "die") {
          dLog("Received DEATH");
          break;
        }

        for (auto mod : modules) {
          dLog("CHECKING " + mod->name);
          if (mod->name == instruction) {
            dLog("Initiating " + mod->name);
            if (module != nullptr) {
              module->teardown();
            }
            module = mod;
            module->setup();
          }
        }
      } else {
        // Normal loop
        if (module != nullptr) {
          long int sleepTime{module->render()};
          if (sleepTime > 1000) {
            sleepTime = sleepTime % 1000;
            sleep(sleepTime / 1000);
          }
          if (sleepTime > 0) {
            usleep(sleepTime * 1000);
          }
        } else {
          sleep(1);
        }
      }
    } while (!shouldExit);
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
