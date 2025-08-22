#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../../types.hpp"

namespace json {
    std::shared_ptr<NumberToken> parseNumber(std::string, std::regex = std::regex("[ \\n\\r\\t]"));
}
