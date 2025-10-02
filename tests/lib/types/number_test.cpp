#include <doctest/doctest.h>
#include <memory>
#include <sstream>
#include "../../../src/lib/types.hpp"

TEST_CASE("NumberToken writeTo")
{
    auto token = std::make_shared<json::NumberToken>(0, 42.0);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "NumberToken { skip: 0, value: 42.0000 }");
}