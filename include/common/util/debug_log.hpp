#pragma once

#ifdef DEBUG
#include <iostream>
#endif

template <typename T> void dLog(const T str, char endln = '\n') {
#ifdef DEBUG
  std::cout << str << endln;
#endif
}
