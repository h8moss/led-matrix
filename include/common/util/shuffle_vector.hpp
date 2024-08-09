#pragma once

#include <vector>

// template <typename T> std::vector<T> shuffle(std::vector<T> vector);

template <typename T>
std::vector<T> shuffle(std::vector<T> v)
{
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(v.begin(), v.end(), g);

  return v;
}
