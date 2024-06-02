#include "modules/images/images_module.hpp"
#include "common/util/debug_log.hpp"
#include "modules/images/images_configuration.hpp"

#include "led-matrix.h"

#include <Magick++/Geometry.h>
#include <Magick++/Image.h>
#include <cmath>
#include <cstdint>
#include <graphics.h>

Images::ImagesModule::ImagesModule(ICanvas *canvas)
    : Module(canvas, "images", "Display images in the led matrix"),
      config{Images::Configuration::defaults}, currentImage{}, images{} {}

void Images::ImagesModule::setup()
{
  images = std::vector<Magick::Image>(config.images.size());
  imageBuffers = std::vector<uint8_t *>(config.images.size());
  bufferW = std::vector<int>(config.images.size());
  bufferH = std::vector<int>(config.images.size());

  for (int i{}; i < images.size(); ++i)
  {
    const std::string filename = config.images[i];
    // FileInfo *file_info = NULL;

    Magick::Image img{};
    img.read(config.images[i]);

    int resizeW{};
    int resizeH{};
    if (img.size().width() != canvas->getWidth() || img.size().height() != canvas->getHeight())
    {

      if (config.fit == Images::ImageFit::box)
      {
        // Scale image until largest side matches the matrix size
        if (img.size().width() > img.size().height())
        {
          resizeW = canvas->getWidth();
          resizeH = (img.size().height() * resizeW) / img.size().width();
        }
        else
        {
          resizeH = canvas->getHeight();
          resizeW = (img.size().width() * resizeH) / img.size().height();
        }
      }
      else if (config.fit == Images::ImageFit::crop)
      {
        // Scale image until smallest side matches the matrix size
        if (img.size().width() < img.size().height())
        {
          resizeW = canvas->getWidth();
          resizeH = (img.size().height() * resizeW) / img.size().width();
        }
        else
        {
          resizeH = canvas->getHeight();
          resizeW = (img.size().width() * resizeH) / img.size().height();
        }
      }
      else if (config.fit == Images::ImageFit::place)
      {
        // do nothing
      }
      else if (config.fit == Images::ImageFit::stretch)
      {
        // Scale image until both sides match the matrix size
        resizeW = canvas->getWidth();
        resizeH = canvas->getHeight();
      }
      else
      {
        throw "Unknown image fit";
      }
    }
    if (resizeW + resizeH != 0)
    {
      img.resize(Magick::Geometry(resizeW, resizeH));
    }

    img.modifyImage();

    bufferW[i] = std::min((int)img.size().width(), canvas->getWidth());
    bufferH[i] = std::min((int)img.size().height(), canvas->getHeight());

    imageBuffers[i] = new uint8_t[img.size().width() * img.size().height() * 3];

    for (int x{}; x < bufferW[i]; ++x)
    {
      for (int y{}; y < bufferH[y]; ++y)
      {
        dLog(std::to_string(x + y * bufferW[i]) + "/" + std::to_string(bufferW[i] * bufferH[i]));
        // set image buffer quantum values
        // red
        imageBuffers[i][x + y * bufferW[i] * 3] = img.pixelColor(x, y).redQuantum();
        // green
        imageBuffers[i][x + y * bufferW[i] * 3 + 1] = img.pixelColor(x, y).greenQuantum();
        // blue
        imageBuffers[i][x + y * bufferW[i] * 3 + 2] = img.pixelColor(x, y).blueQuantum();
      }
    }

    images[i] = img;
  }
}

long int Images::ImagesModule::render()
{
  auto img{images[currentImage]};
  auto buffer{imageBuffers[currentImage]};
  int buffW{bufferW[currentImage]};
  int buffH{bufferH[currentImage]};

  canvas->clear();

  rgb_matrix::SetImage(canvas->getCanvas(), 0, 0, buffer, buffW * buffH * 3, buffW, buffH, false);

  return 1000 * 1000;
}

void Images::ImagesModule::teardown() { canvas->clear(); }

void Images::ImagesModule::addFlags(CLI::App *app)
{
  auto cmd{app->add_subcommand(this->name, this->description)};

  cmd->add_option("--image,-i", config.images,
                  "An image to showcase, can be passed more than once");
  cmd->add_option("--duration,-d", config.durations,
                  "The time the image should be on screen in ms. If passed "
                  "more than once, matches the correspoinding image");
  cmd->add_option("--fit", config.fit, "How to fit the image into the matrix")
      ->transform(CLI::CheckedTransformer(Images::Configuration::imageFitMap,
                                          CLI::ignore_case));
  cmd->add_option("--x-align,-x", config.xAlignment,
                  "The alignment of the image on the x axis")
      ->transform(CLI::CheckedTransformer(Images::Configuration::alignmentMap,
                                          CLI::ignore_case));
  cmd->add_option("--y-align,-y", config.yAlignment,
                  "The alignment of the image on the y axis")
      ->transform(CLI::CheckedTransformer(Images::Configuration::alignmentMap,
                                          CLI::ignore_case));
  cmd->add_flag("--no-loop", config.exitOnEnd,
                "If passed, the images will not loop and instead the program "
                "will exit after once run");
  cmd->add_flag("--shuffle,-s", config.shuffleImages,
                "Shuffle the images before displaying them");
}

void Images::ImagesModule::readArguments(
    std::map<std::string, std::vector<std::string>> args) {}

Images::ImagesModule::~ImagesModule() {}
