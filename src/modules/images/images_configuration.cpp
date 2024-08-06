#include "modules/images/images_configuration.hpp"

#include <map>

Images::Configuration Images::Configuration::defaults = {
    .images = {},
    .durations = {},
    .fit = Images::ImageFit::stretch,
    .xAlignment = Images::Alignment::leading,
    .yAlignment = Images::Alignment::leading,
    .exitOnEnd = false,
    .shuffleImages = false,
};

int Images::Configuration::defaultDuration = 1000;

std::map<std::string, Images::ImageFit> Images::Configuration::imageFitNames = {
    {"box", Images::ImageFit::box},
    {"crop", Images::ImageFit::crop},
    {"place", Images::ImageFit::place},
    {"stretch", Images::ImageFit::stretch},
};

std::map<std::string, Images::Alignment> Images::Configuration::alignmentNames =
    {
        {"center", Images::Alignment::center},
        {"leading", Images::Alignment::leading},
        {"trailing", Images::Alignment::trailing},
};
