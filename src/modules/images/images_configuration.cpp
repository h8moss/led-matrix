#include "modules/images/images_configuration.hpp"

Images::Configuration Images::Configuration::defaults = {
    .images = {},
    .durations = {},
    .fit = Images::ImageFit::stretch,
    .xAlignment = Images::Alignment::leading,
    .yAlignment = Images::Alignment::leading,
    .exitOnEnd = false,
    .shuffleImages = false,
};

std::map<std::string, Images::Alignment> Images::Configuration::alignmentMap = {
    {"leading", Images::Alignment::leading},
    {"center", Images::Alignment::center},
    {"trailing", Images::Alignment::trailing},
};

std::map<std::string, Images::ImageFit> Images::Configuration::imageFitMap = {
    {"stretch", Images::ImageFit::stretch},
    {"box", Images::ImageFit::box},
    {"place", Images::ImageFit::place},
    {"crop", Images::ImageFit::crop}};
