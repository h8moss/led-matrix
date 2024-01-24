#pragma once

#include "colors_configuration.hpp"
#include "../../common/util/array_to_vector.hpp"

namespace ColorsModule {
  ColorsConfiguration parseArguments(int argc, char** args);
}