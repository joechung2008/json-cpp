#include <doctest/doctest.h>
#include <memory>
#include <sstream>
#include "../../../src/lib/types.hpp"

TEST_CASE("StringToken writeTo")
{
    auto token = std::make_shared<json::StringToken>(0, "hello");
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "StringToken { skip: 0, value: \"hello\" }");
}