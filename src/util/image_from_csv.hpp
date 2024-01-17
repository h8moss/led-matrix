#pragma once

#include <string>

#include "../models/image.hpp"

/// Converts csv of the form
/// ffaacc,0888ff,...,ffffff
/// Into an `Image`
Image imageFromCSV(std::string csv);