#pragma once
#include <memory>
#include <regex>
#include <string>
#include "../types.hpp"

namespace json {
    std::shared_ptr<StringToken> parseString(std::string);
}
