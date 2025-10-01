#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json
{
    auto parsePair(const std::string&, const std::regex&) -> std::shared_ptr<PairToken>;
}
