#pragma once

#include <string>
#include <vector>

/// Turns a c-style array into a std::string vector
std::vector<std::string> arrayToVector(int size, char **array);