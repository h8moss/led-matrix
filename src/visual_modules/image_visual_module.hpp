#pragma once

#include "visual_module.hpp"
#include "../models/image.hpp"

class ImageVisualModule : public VisualModule { 
public:
  virtual void draw(Canvas *canvas) const override;

  Image image;

  ImageVisualModule(Image p_image);
};