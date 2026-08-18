#pragma once

#include <string>
#ifdef DEBUG
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#endif

template <typename T> void dLog(const T str, char endln = '\n') {
#ifdef DEBUG
  auto tp = std::chrono::system_clock::now();
  std::time_t t = std::chrono::system_clock::to_time_t(tp);
  std::tm *now = std::localtime(&t);

  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                tp.time_since_epoch()) %
            1000;

  std::ostringstream oss;
  oss << std::setfill('0') << now->tm_mday << "/" << (now->tm_mon + 1) << "/"
      << (1900 + now->tm_year) << " - " << std::setw(2) << now->tm_hour << ":"
      << std::setw(2) << now->tm_min << ":" << std::setw(2) << now->tm_sec
      << "." << std::setw(3) << ms.count();

  std::string finalTime = oss.str();
  std::cout << "(" << finalTime << ") " << str << endln;
#endif
}
