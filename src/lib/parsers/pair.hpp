#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json
{
    std::shared_ptr<PairToken> parsePair(const std::string&, const std::regex&);
}
