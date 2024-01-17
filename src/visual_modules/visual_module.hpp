#pragma once

#include "led-matrix.h"

using rgb_matrix::Canvas;

class VisualModule {
  public:
  virtual void draw(Canvas *canvas) const = 0;
};