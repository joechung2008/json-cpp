#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json
{
    auto parseNumber(const std::string&, const std::regex&) -> std::shared_ptr<NumberToken>;
}
