#include "modules/images/images_module.hpp"

#include "common/util/arg_parser.hpp"
#include "common/util/debug_log.hpp"
#include "common/util/enum_checked_transformer.hpp"
#include "common/util/shuffle_vector.hpp"
#include "modules/images/images_configuration.hpp"

#include <Magick++.h>
#include <cmath>
#include <graphics.h>

Images::ImagesModule::ImagesModule(ICanvas *canvas)
    : Module(canvas, "images", "Display images in the led matrix"),
      config{Images::Configuration::defaults}, loopCount{}, images{} {}

void Images::ImagesModule::setup() {
  loopCount = 0;
  images = std::vector<Magick::Image>(config.images.size());
  pixels = std::vector<std::vector<Color>>(config.images.size());

  for (size_t i{}; i < images.size(); ++i) {
    const std::string filename = config.images[i];

    Magick::Image img{};
    img.read(config.images[i]);

    int resizeW{};
    int resizeH{};
    if (img.size().width() != canvas->getWidth() ||
        img.size().height() != canvas->getHeight()) {

      if (config.fit == Images::ImageFit::box) {
        // Scale image until largest side matches the matrix size
        if (img.size().width() > img.size().height()) {
          resizeW = canvas->getWidth();
          resizeH = (img.size().height() * resizeW) / img.size().width();
        } else {
          resizeH = canvas->getHeight();
          resizeW = (img.size().width() * resizeH) / img.size().height();
        }
      } else if (config.fit == Images::ImageFit::crop) {
        // Scale image until smallest side matches the matrix size
        if (img.size().width() < img.size().height()) {
          resizeW = canvas->getWidth();
          resizeH = (img.size().height() * resizeW) / img.size().width();
        } else {
          resizeH = canvas->getHeight();
          resizeW = (img.size().width() * resizeH) / img.size().height();
        }
      } else if (config.fit == Images::ImageFit::place) {
        // do nothing
      } else if (config.fit == Images::ImageFit::stretch) {
        // Scale image until both sides match the matrix size
        resizeW = canvas->getWidth();
        resizeH = canvas->getHeight();
      } else {
        throw "Unknown image fit";
      }
    }
    dLog("RESIZE: " + std::to_string(resizeW) + ", " + std::to_string(resizeH));
    if (resizeW + resizeH != 0) {
      img.resize(Magick::Geometry(std::to_string(resizeW) + "x" +
                                  std::to_string(resizeH) + "!"));
    }

    img.modifyImage();
    img.syncPixels();

    dLog("FINAL SIZE: " + std::to_string(img.size().width()) + ", " +
         std::to_string(img.size().height()));

    int minSizeW{std::min((int)img.size().width(), canvas->getWidth())};
    int minSizeH{std::min((int)img.size().height(), canvas->getHeight())};

    Magick::PixelPacket *pixelPacks{img.getPixels(0, 0, minSizeW, minSizeH)};
    pixels[i] = std::vector<Color>(minSizeW * minSizeH);

    for (size_t pixel{}; pixel < minSizeW * minSizeH; ++pixel) {
      Color c{ScaleQuantumToChar(pixelPacks[pixel].red),
              ScaleQuantumToChar(pixelPacks[pixel].green),
              ScaleQuantumToChar(pixelPacks[pixel].blue)};
      pixels[i][pixel] = c;
    }
    images[i] = img;
  }
  if (config.shuffleImages) {
    images = shuffle(images);
  }
}

long int Images::ImagesModule::render() {
  if (config.exitOnEnd && loopCount >= images.size()) {
    return -1; // exit
  }

  int currentImage{loopCount % (int)images.size()};
  if (currentImage && images.size() == 1) {
    return 100; // Just one image and it has already been drawn
  }
  auto img{images[currentImage]};
  auto currentPixels{pixels[currentImage]};

  canvas->clear();

  int minSizeW{std::min((int)img.size().width(), canvas->getWidth())};
  int minSizeH{std::min((int)img.size().width(), canvas->getHeight())};

  int xOffset{};
  int yOffset{};

  int w{(int)img.size().width()};
  int h{(int)img.size().height()};

  if (config.xAlignment == Images::Alignment::center) {
    xOffset = (canvas->getHeight() - w) / 2;
  } else if (config.xAlignment == Images::Alignment::trailing) {
    xOffset = (canvas->getHeight() - w);
  }

  if (config.yAlignment == Images::Alignment::center) {
    yOffset = (canvas->getHeight() - h) / 2;
  } else if (config.yAlignment == Images::Alignment::trailing) {
    yOffset = (canvas->getHeight() - h);
  }

  for (size_t pixelIndex{}; pixelIndex < currentPixels.size(); ++pixelIndex) {
    int x{(int)pixelIndex % minSizeW};
    int y{(int)pixelIndex / minSizeH};

    auto px{currentPixels[pixelIndex]};

    canvas->setPixel(x + xOffset, y + yOffset, px);
  }

  int duration{Images::Configuration::defaultDuration};
  if (currentImage < config.durations.size()) {
    duration = config.durations[currentImage];
  } else if (config.durations.size() > 0) {
    duration = config.durations[config.durations.size() - 1];
  }

  ++loopCount;

  return 1000 * duration;
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
      ->transform(EnumCheckedTransformer(
          {{"box", Images::ImageFit::box},
           {"crop", Images::ImageFit::crop},
           {"place", Images::ImageFit::place},
           {"stretch", Images::ImageFit::stretch}},
          {{Images::ImageFit::box,
            "Shrinks the image until its largest side fits in the matrix "},
           {Images::ImageFit::crop,
            "Shrinks the image until its smallest side fits in the matrix"},
           {Images::ImageFit::place, "Places the image exactly as it is"},
           {Images::ImageFit::stretch,
            "Stretches each side to be exactly as big as the matrix"}}));

  cmd->add_option("--x-align,-x", config.xAlignment,
                  "The alignment of the image on the x axis")
      ->transform(EnumCheckedTransformer(
          {{"leading", Images::Alignment::leading},
           {"trailing", Images::Alignment::trailing},
           {"center", Images::Alignment::center}},
          {{Images::Alignment::leading,
            "The image is to the left of the canvas"},
           {Images::Alignment::trailing,
            "The image is to the right of the canvas"},
           {Images::Alignment::center,
            "The image is to the center of the canvas"}}));
  cmd->add_option("--y-align,-y", config.yAlignment,
                  "The alignment of the image on the y axis")
      ->transform(EnumCheckedTransformer(
          {{"leading", Images::Alignment::leading},
           {"trailing", Images::Alignment::trailing},
           {"center", Images::Alignment::center}},
          {{Images::Alignment::leading,
            "The image is to the top of the canvas"},
           {Images::Alignment::trailing,
            "The image is to the bottom of the canvas"},
           {Images::Alignment::center,
            "The image is to the center of the canvas"}}));

  cmd->add_flag("--no-loop", config.exitOnEnd,
                "If passed, the images will not loop and instead the program "
                "will exit after once run");
  cmd->add_flag("--shuffle,-s", config.shuffleImages,
                "Shuffle the images before displaying them");
}

void Images::ImagesModule::readArguments(
    std::map<std::string, std::vector<std::string>> map) {
  config = Images::Configuration::defaults;

  if (map.count("image")) {
    config.images = map["image"];
  }
  if (map.count("duration")) {
    config.durations = {std::vector<int>(map["duration"].size())};
    for (size_t i{}; i < map["duration"].size(); ++i) {
      config.durations[i] = std::stoi(map["duration"][i]);
    }
  }
  // TODO: Enums! Use colors.animation as a guide
  if (map.count("fit")) {
    std::string value = ArgParser::ensureSingle(map, "fit");
  }
}

Images::ImagesModule::~ImagesModule() {}
