#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json
{
    auto parseValue(const std::string&,
                    const std::regex& delimiters = std::regex(R"([ \n\r\t])")) -> std::shared_ptr<Token>;
}
