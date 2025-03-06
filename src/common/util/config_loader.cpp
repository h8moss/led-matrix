#include "common/util/config_loader.hpp"

#include <fstream>
#include <string>

rgb_matrix::RGBMatrix::Options loadConfig() {

  std::fstream f{};
  f.open("./matrix.conf");

  rgb_matrix::RGBMatrix::Options options;

  std::string hardwareMapping = "regular";
  int rows = 64;
  int cols = 64;
  int chainLength = 1;
  int parallel = 1;
  bool showRefreshRate = false;

  std::string line{};
  while (getline(f, line)) {
    size_t position = line.find('=');
    if (position == std::string::npos) {
      throw "Problem parsing config. Make sure each line in the config has an "
            "= sign";
    }

    std::string key{line.substr(0, position)};
    std::string value{line.substr(position)};

    if (key == "hardware_mapping") {
      hardwareMapping = value;
    } else if (key == "rows") {
      rows = std::stoi(value);
    } else if (key == "cols") {
      cols = std::stoi(value);
    } else if (key == "chain_length") {
      chainLength = std::stoi(value);
    } else if (key == "parallel") {
      parallel = std::stoi(value);
    } else if (key == "show_refresh_rate") {
      showRefreshRate = std::stoi(value) == 1;
    }
  }

  options.hardware_mapping = hardwareMapping.c_str();
  options.rows = rows;
  options.cols = cols;
  options.chain_length = chainLength;
  options.parallel = parallel;
  options.show_refresh_rate = showRefreshRate;

  f.close();

  return options;
}
