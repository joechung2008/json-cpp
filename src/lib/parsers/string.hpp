#pragma once
#include <memory>
#include <string>
#include "../types.hpp"

namespace json
{
    std::shared_ptr<StringToken> parseString(const std::string&);
}
