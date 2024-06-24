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
