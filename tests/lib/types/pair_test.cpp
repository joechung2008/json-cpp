#include <doctest/doctest.h>
#include <memory>
#include <sstream>
#include "../../../src/lib/types.hpp"

TEST_CASE("PairToken writeTo")
{
    auto key = std::make_shared<json::StringToken>(0, "key");
    auto value = std::make_shared<json::NumberToken>(0, 42.0);
    auto token = std::make_shared<json::PairToken>(0, key, value);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    std::string expected = "PairToken {\n    key: StringToken { skip: 0, value: \"key\" },\n    value: NumberToken { "
                           "skip: 0, value: 42.0000 }\n}";
    CHECK(oss.str() == expected);
}