#pragma once
#include "common/util/better_canvas.hpp"
#include "modules/module.hpp"
#include "modules/colors/colors_configuration.hpp"

namespace Colors
{
    class ColorsModule : public Module<Colors::ConfigurationWithAnimation>
    {
    public:
        ColorsModule(BetterCanvas *canvas);
        ~ColorsModule();

        void setup() override;
        int render() override;
        void teardown() override;

    private:
        Module<Colors::Configuration> *renderer;
    };
}
