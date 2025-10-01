#pragma once
#include <memory>
#include <string>
#include "../types.hpp"

namespace json
{
    auto parseArray(const std::string&) -> std::shared_ptr<ArrayToken>;
}
