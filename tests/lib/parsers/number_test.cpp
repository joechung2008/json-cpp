#include "doctest.h"
#include <regex>
#include <memory>
#include "../../../src/lib/parsers/value.hpp"
#include "../../../src/lib/types.hpp"

TEST_CASE("parseValue: positive integer")
{
    auto token = json::parseValue("42");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == 42);
}

TEST_CASE("parseValue: negative integer")
{
    auto token = json::parseValue("-7");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == -7);
}

TEST_CASE("parseValue: positive sign (should fail)")
{
    CHECK_THROWS_AS(json::parseValue("+5"), std::runtime_error);
}

TEST_CASE("parseValue: leading zero (should fail)")
{
    CHECK_THROWS_AS(json::parseValue("01"), std::runtime_error);
}

TEST_CASE("parseValue: decimal number")
{
    auto token = json::parseValue("3.1415");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(3.1415));
}

TEST_CASE("parseValue: negative decimal")
{
    auto token = json::parseValue("-0.99");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(-0.99));
}

TEST_CASE("parseValue: exponent positive")
{
    auto token = json::parseValue("1e6");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(1e6));
}

TEST_CASE("parseValue: exponent negative")
{
    auto token = json::parseValue("2.5e-3");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(0.0025));
}

TEST_CASE("parseValue: exponent with plus sign")
{
    auto token = json::parseValue("7e+2");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(700));
}

TEST_CASE("parseValue: exponent with uppercase E")
{
    auto token = json::parseValue("6E3");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(6000));
}

TEST_CASE("parseValue: just decimal point (should fail)")
{
    CHECK_THROWS_AS(json::parseValue("."), std::runtime_error);
}

TEST_CASE("parseValue: trailing decimal point (should succeed)")
{
    auto token = json::parseValue("5.");
    CHECK(dynamic_cast<json::NumberToken *>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken *>(token.get());
    CHECK(num->value == doctest::Approx(5));
}

TEST_CASE("parseValue: leading decimal point (should fail)")
{
    CHECK_THROWS_AS(json::parseValue(".5"), std::runtime_error);
}
