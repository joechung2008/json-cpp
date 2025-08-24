#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json {
    std::shared_ptr<NumberToken> parseNumber(const std::string&, const std::regex& = std::regex(R"([ \n\r\t])"));
}
