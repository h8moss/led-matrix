#include "modules/images/images_module.hpp"

Images::ImagesModule::ImagesModule(ICanvas *canvas)
    : Module(canvas, "images", "Display images in the led matrix"),
      config{Images::Configuration::defaults}, currentImage{}, images{} {}

void Images::ImagesModule::setup() {
  currentImage = 0;
  images = {};

  for (auto c : config.images) {
    Magick::Image img{};
    img.read(c);
    images.push_back(c);
  }
}

long int Images::ImagesModule::render() {
  size_t index{(size_t)currentImage % images.size()};
  ++currentImage;

  auto image{images[index]};

  // paint image
  for (int x{}; x < canvas->getWidth(); x++) {
    for (int y{}; y < canvas->getHeight(); y++) {
      canvas->setPixel(x, y, Color::fromMagickColor(image.pixelColor(x, y)));
    }
  }

  return config.durations[index];
}

void Images::ImagesModule::teardown() { canvas->clear(); }

void Images::ImagesModule::addFlags(CLI::App *app) {}

void Images::ImagesModule::readArguments(
    std::map<std::string, std::vector<std::string>> args) {}

Images::ImagesModule::~ImagesModule() {}
