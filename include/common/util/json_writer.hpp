#pragma once

#include <string>
#include <vector>

// Escapes a string's contents for use inside a JSON string literal (does not
// add the surrounding quotes).
std::string jsonEscape(std::string value);

// Wraps a string in double quotes, escaping its contents.
std::string jsonString(std::string value);

std::string jsonBool(bool value);

// Builds a `"key": value` pair. `valueJson` must already be valid JSON (use
// jsonString/jsonBool/jsonArray/jsonObject to build it).
std::string jsonField(std::string key, std::string valueJson);

// Joins already-built JSON object/value strings into a `[...]` array.
std::string jsonArray(std::vector<std::string> items);

// Joins already-built `jsonField` strings into a `{...}` object.
std::string jsonObject(std::vector<std::string> fields);
