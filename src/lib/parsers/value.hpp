#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json {
    std::shared_ptr<Token> parseValue(std::string, std::regex delimiters = std::regex("[ \\n\\r\\t]"));
}
