#pragma once
#include <memory>
#include <string>
#include "../types.hpp"

namespace json {
    std::shared_ptr<ArrayToken> parseArray(const std::string&);
}
