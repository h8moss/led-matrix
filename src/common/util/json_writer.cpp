#include "common/util/json_writer.hpp"

#include <sstream>
#include <iomanip>

std::string jsonEscape(std::string value) {
  std::string result{};

  for (char c : value) {
    switch (c) {
    case '"':
      result += "\\\"";
      break;
    case '\\':
      result += "\\\\";
      break;
    case '\n':
      result += "\\n";
      break;
    case '\r':
      result += "\\r";
      break;
    case '\t':
      result += "\\t";
      break;
    default:
      if (static_cast<unsigned char>(c) < 0x20) {
        std::ostringstream stream{};
        stream << "\\u" << std::hex << std::setw(4) << std::setfill('0')
               << static_cast<int>(c);
        result += stream.str();
      } else {
        result += c;
      }
    }
  }

  return result;
}

std::string jsonString(std::string value) {
  return "\"" + jsonEscape(value) + "\"";
}

std::string jsonBool(bool value) { return value ? "true" : "false"; }

std::string jsonField(std::string key, std::string valueJson) {
  return jsonString(key) + ": " + valueJson;
}

std::string jsonArray(std::vector<std::string> items) {
  std::string result{"["};

  for (size_t i{}; i < items.size(); ++i) {
    if (i > 0) {
      result += ", ";
    }
    result += items[i];
  }

  result += "]";
  return result;
}

std::string jsonObject(std::vector<std::string> fields) {
  std::string result{"{"};

  for (size_t i{}; i < fields.size(); ++i) {
    if (i > 0) {
      result += ", ";
    }
    result += fields[i];
  }

  result += "}";
  return result;
}
