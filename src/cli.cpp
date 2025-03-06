#include "common/canvas/better_canvas.hpp"
#include "common/canvas/debug_canvas.hpp"
#include "modules/colors/colors_module.hpp"
#include "modules/game-of-life/game_of_life_module.hpp"
#include "modules/images/images_module.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_module.hpp"

#include "CLI/CLI.hpp"
#include "led-matrix.h"

#include <iostream>
#include <signal.h>
#include <sys/select.h>
#include <unistd.h>
#include <vector>

#include "CLI/CLI.hpp"
#include "Magick++.h"

volatile bool interruptReceived = false;

static void Interrupt(int signo) { interruptReceived = true; }

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);
  CLI::App app{"Led matrix"};
  argv = app.ensure_utf8(argv);
  app.require_subcommand(1);

  srand((unsigned int)time(nullptr));

  try {
    ICanvas *canvas;

#ifdef DEVLAPTOP

    canvas = new DebugCanvas();

#else

    // rgb_matrix::RGBMatrix::Options defaults;
    // defaults.hardware_mapping = "regular";
    // defaults.rows = 64;
    // defaults.cols = 64;
    // defaults.chain_length = 1;
    // defaults.parallel = 1;
    // defaults.show_refresh_rate = false;
    canvas = new BetterCanvas();

#endif

    std::vector<Module *> modules{
        new Colors::ColorsModule(canvas), new GameOfLife::GOLModule(canvas),
        new TimeDate::TimeDateModule(canvas), new Images::ImagesModule(canvas)};

    for (auto mod : modules) {
      mod->addFlags(&app);
    }

    app.parse(argc, argv);

    signal(SIGTERM, Interrupt);
    signal(SIGINT, Interrupt);
    signal(SIGKILL, Interrupt);

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    Module *module{nullptr};
    for (auto mod : modules) {
      if (app.got_subcommand(mod->name)) {
        module = mod;
        break;
      }
    }

    if (module == nullptr) {
      std::cout << app.help() << std::endl;
      return 1;
    }

    module->setup();
    std::cout << "Press Ctrl-C to stop :)" << std::endl;

    while (!interruptReceived) {
      long int sleepTime{module->render()};

      if (sleepTime < 0) {
        break;
      }
      unsigned long int finalSleepTime{(unsigned long int)sleepTime};

      if (finalSleepTime > 1000000) {
        sleep(finalSleepTime / 1000000);
        finalSleepTime = finalSleepTime % 1000000;
      }
      if (finalSleepTime > 0) {
        usleep(finalSleepTime);
      }
    }

    module->teardown();
    std::cout << "Ctrl-C received, Exiting" << std::endl;
    module = nullptr;

    for (auto mod : modules) {
      delete mod;
    }

    delete canvas;
    canvas = nullptr;
  } catch (const CLI::ParseError &err) {
    return app.exit(err);
  } catch (const char *err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (const std::string err) {
    std::cerr << err << std::endl;
    return 1;
  } catch (const std::exception &err) {
    std::cerr << "Something went wrong!" << '\n';
    std::cerr << err.what() << std::endl;
  }
  return 0;
}
