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
