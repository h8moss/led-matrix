#include "common/util/pad_zeros.hpp"
#include <string>

std::string padZeros(int number, std::string::size_type length) {
  std::string numStr{std::to_string(number)};
  while (numStr.length() < length)
    numStr = '0' + numStr;

  return numStr;
}
