#pragma once

#include <string>
#ifdef DEBUG
#include <ctime>
#include <iostream>
#endif

template <typename T> void dLog(const T str, char endln = '\n') {
#ifdef DEBUG
  std::time_t t = std::time(nullptr);
  std::tm *now = std::localtime(&t);
  std::string finalTime{
      std::to_string(now->tm_mday) + "/" + std::to_string(now->tm_mon) + "/" +
      std::to_string(now->tm_year) + " - " + std::to_string(now->tm_hour) +
      ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec) +
      "."};

  std::cout << "(" << finalTime << ") " << str << endln;
#endif
}
