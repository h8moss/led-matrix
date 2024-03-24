#include <iostream>

template <typename T> void dLog(const T str) {
#ifdef DEBUG
  std::cout << str << '\n';
#endif
}
