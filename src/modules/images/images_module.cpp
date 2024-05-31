#include "modules/images/images_module.hpp"
#include "common/util/debug_log.hpp"
#include "modules/images/images_configuration.hpp"

#include <Magick++/Geometry.h>
#include <Magick++/Image.h>
#include <cmath>
#include <cstdint>
#include <graphics.h>

Images::ImagesModule::ImagesModule(ICanvas *canvas)
    : Module(canvas, "images", "Display images in the led matrix"),
      config{Images::Configuration::defaults}, currentImage{}, images{} {}

void Images::ImagesModule::setup() {
  currentImage = 0;
  images = {std::vector<Magick::Image>(config.images.size())};
  imageBuffers = {std::vector<uint8_t *>(config.images.size())};

  for (size_t i{}; i < config.images.size(); ++i) {
    auto c{config.images[i]};

    Magick::Image img{};
    img.read(c);

    unsigned long imgW{img.size().width()};
    unsigned long imgH{img.size().height()};

    uint8_t *buffer{new uint8_t[3 * imgW * imgH]};

    if (config.fit == Images::ImageFit::crop) {
      float ratioW{(float)imgW / (float)canvas->getWidth()};
      float ratioH{(float)imgH / (float)canvas->getHeight()};
      float finalRatio{std::min(ratioW, ratioH)};
      img.scale(
          Magick::Geometry((float)imgW / finalRatio, (float)imgH / finalRatio));
    } else if (config.fit == Images::ImageFit::stretch) {
      img.resize(Magick::Geometry(canvas->getWidth(), canvas->getHeight()));
      img.syncPixels();
    } else if (config.fit == Images::ImageFit::place) {
      // Do nothing
    } else if (config.fit == Images::ImageFit::box) {
      float ratioW{(float)imgW / (float)canvas->getWidth()};
      float ratioH{(float)imgH / (float)canvas->getHeight()};
      float finalRatio{std::max(ratioW, ratioH)};
      img.scale(
          Magick::Geometry((float)imgW / finalRatio, (float)imgH / finalRatio));

    } else {
      throw "Unkown fitting strategy";
    }

    for (size_t i{}; i < imgH; ++i) {
      for (size_t j{}; j < imgW; ++j) {
        auto color{img.pixelColor(j, i)};
        buffer[(i * imgW + j) * 3 + 0] = color.redQuantum();
        buffer[(i * imgW + j) * 3 + 1] = color.greenQuantum();
        buffer[(i * imgW + j) * 3 + 2] = color.blueQuantum();
      }
    }

    images[i] = img;
    imageBuffers[i] = buffer;
  }
}

long int Images::ImagesModule::render() {
  // If there is just one image and we already show it
  if (currentImage != 0 && images.size() == 1) {
    return 20000; // return 20ms
  }

  canvas->clear();
  size_t index{(size_t)currentImage % images.size()};
  ++currentImage;

  auto image{images[index]};

  int xOffset{};
  int yOffset{};

  if (config.xAlignment == Images::Alignment::center) {
    xOffset = (canvas->getWidth() - image.size().width()) / 2;
  } else if (config.xAlignment == Images::Alignment::trailing) {
    xOffset = (canvas->getWidth() - image.size().width());
  }

  if (config.yAlignment == Images::Alignment::center) {
    yOffset = (canvas->getHeight() - image.size().height()) / 2;
  } else if (config.yAlignment == Images::Alignment::trailing) {
    yOffset = (canvas->getHeight() - image.size().height());
  }

  // paint image
  /*
  for (int x{}; x < std::min(canvas->getWidth(), (int)image.size().width());
       x++) {
    for (int y{}; y < std::min(canvas->getHeight(), (int)image.size().height());
         y++) {
      if (x == 0) {
        auto color{Color::fromMagickColor(image.pixelColor(x, y))};
        dLog(color.string());
      }
      canvas->setPixel(x + xOffset, y + yOffset,
                       Color::fromMagickColor(image.pixelColor(x, y)));
    }
  }
*/
  rgb_matrix::SetImage(canvas, xOffset, yOffset, imageBuffers[index],
                       image.size().width() * image.size().height * 3,
                       image.size().width(), image.size().height(), false);
  int duration{1000};
  if (config.durations.size() < index + 1) {
    if (config.durations.size() > 1) {
      duration = config.durations[config.durations.size() - 1];
    }
  } else {
    duration = config.durations[index];
  }

  return duration * 1000;
}

void Images::ImagesModule::teardown() { canvas->clear(); }

void Images::ImagesModule::addFlags(CLI::App *app) {
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
