#pragma once
#include <string>

#include "../models/color.hpp"

#include "led-matrix.h"

void drawText(rgb_matrix::Canvas *canvas, int x, int y, std::string text, Color color);