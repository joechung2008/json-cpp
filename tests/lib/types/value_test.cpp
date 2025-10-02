#include <doctest/doctest.h>
#include <memory>
#include <sstream>
#include "../../../src/lib/types.hpp"

TEST_CASE("NullToken writeTo")
{
    auto token = std::make_shared<json::NullToken>(0);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "NullToken { skip: 0 }");
}

TEST_CASE("FalseToken writeTo")
{
    auto token = std::make_shared<json::FalseToken>(0);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "FalseToken { skip: 0, value: false }");
}

TEST_CASE("TrueToken writeTo")
{
    auto token = std::make_shared<json::TrueToken>(0);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "TrueToken { skip: 0, value: true }");
}