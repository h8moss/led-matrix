#include "common/util/better_canvas.hpp"
#include "led-matrix.h"
#include "modules/colors/colors_module.hpp"
#include "modules/game-of-life/game_of_life_module.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_module.hpp"

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <vector>

volatile bool interruptReceived = false;
static void Interrupt(int signo) { interruptReceived = true; }

static void printUsage(std::vector<Module *> modules) {
  std::cout << "Usage:\n";
  std::cout << "\tled-matrix <MODE> [Options]\n";
  std::cout << "\tFunctions:\n";
  for (auto mod : modules) {
    std::cout << "\t\t" << mod->name << '\n';
  }
}

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
      printUsage(modules);
      return 1;
    }

    signal(SIGTERM, Interrupt);
    signal(SIGINT, Interrupt);

    Module *module{nullptr};
    for (auto mod : modules) {
      if (mod->name == argv[1]) {
        module = mod;
        break;
      }
    }

    if (module == nullptr) {
      printUsage(modules);
      return 1;
    }

    module->configuration->parseArguments(argv, argc);
    if (module->configuration->showHelp) {
      std::cout << module->configuration->getHelp();
      return 1;
    }

    module->setup();
    std::cout << "Press Ctrl-C to stop" << std::endl;

    while (!interruptReceived) {
      usleep(module->render());
    }

    module->teardown();
    std::cout << "Ctrl-C received, Exiting" << std::endl;

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
}
