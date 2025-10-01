#pragma once
#include <memory>
#include <string>
#include "../types.hpp"

namespace json
{
    auto parseString(const std::string&) -> std::shared_ptr<StringToken>;
}
