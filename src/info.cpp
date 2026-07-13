#include "common/util/json_writer.hpp"
#include "modules/colors/colors_module.hpp"
#include "modules/game-of-life/game_of_life_module.hpp"
#include "modules/images/images_module.hpp"
#include "modules/module.hpp"
#include "modules/time-date/time_date_module.hpp"

#include "CLI/CLI.hpp"
#include "Magick++.h"

#include <iostream>

// Placeholder for options that apply across all modules (e.g. matrix
// hardware configuration) rather than to a single module. None are exposed
// via CLI11 yet, so this currently always serializes to `[]`.
std::string globalOptionsJson() { return jsonArray({}); }

std::string optionJson(Module *module, CLI::Option *option) {
  bool isFlag{option->get_expected_min() == 0 && option->get_expected_max() == 0};
  auto enumEntry{module->getEnumOptions().find(option)};
  bool isEnum{enumEntry != module->getEnumOptions().end()};

  std::string type{isFlag ? "flag" : isEnum ? "ENUM" : option->get_type_name()};

  std::vector<std::string> fields{
      jsonField("name", jsonString(option->get_name(false, true))),
      jsonField("description", jsonString(option->get_description())),
      jsonField("type", jsonString(type)),
      jsonField("default", jsonString(option->get_default_str())),
      jsonField("required", jsonBool(option->get_required())),
      jsonField("minItems", std::to_string(option->get_expected_min())),
      jsonField("maxItems", std::to_string(option->get_expected_max())),
  };

  if (isEnum) {
    std::vector<std::string> valuesJson{};
    for (const auto &value : enumEntry->second) {
      valuesJson.push_back(jsonObject({
          jsonField("name", jsonString(value.name)),
          jsonField("value", std::to_string(value.value)),
          jsonField("description", jsonString(value.description)),
      }));
    }
    fields.push_back(jsonField("values", jsonArray(valuesJson)));
  }

  return jsonObject(fields);
}

std::string moduleJson(Module *module, CLI::App *subcommand) {
  std::vector<std::string> optionsJson{};
  for (auto option :
       subcommand->get_options([&](CLI::Option *opt) {
         return opt != subcommand->get_help_ptr();
       })) {
    optionsJson.push_back(optionJson(module, option));
  }

  return jsonObject({
      jsonField("name", jsonString(module->name)),
      jsonField("description", jsonString(module->description)),
      jsonField("options", jsonArray(optionsJson)),
  });
}

int main(int argc, char **argv) {
  Magick::InitializeMagick(*argv);

  std::vector<Module *> modules{
      new Colors::ColorsModule(nullptr), new GameOfLife::GOLModule(nullptr),
      new TimeDate::TimeDateModule(nullptr), new Images::ImagesModule(nullptr)};

  CLI::App app{"Led matrix"};
  for (auto mod : modules) {
    mod->addFlags(&app);
  }

  std::vector<std::string> modulesJson{};
  for (auto mod : modules) {
    auto subcommand{app.get_subcommand(mod->name)};
    modulesJson.push_back(moduleJson(mod, subcommand));
  }

  std::cout << jsonObject({
      jsonField("globalOptions", globalOptionsJson()),
      jsonField("modules", jsonArray(modulesJson)),
  }) << std::endl;

  for (auto mod : modules) {
    delete mod;
  }

  return 0;
}
