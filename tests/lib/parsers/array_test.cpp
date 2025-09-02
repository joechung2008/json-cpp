#include "doctest.h"
#include <regex>
#include <memory>
#include "../../../src/lib/parsers/value.hpp"
#include "../../../src/lib/types.hpp"

TEST_CASE("parseValue: empty array")
{
    auto token = json::parseValue("[]");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 0);
}

TEST_CASE("parseValue: array of numbers")
{
    auto token = json::parseValue("[1,2,3]");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 3);
    for (int i = 0; i < 3; ++i)
        CHECK(dynamic_cast<json::NumberToken *>(arr->elements[i].get()) != nullptr);
}

TEST_CASE("parseValue: array of strings")
{
    auto token = json::parseValue(R"(["a","b","c"])");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 3);
    for (int i = 0; i < 3; ++i)
        CHECK(dynamic_cast<json::StringToken *>(arr->elements[i].get()) != nullptr);
}

TEST_CASE("parseValue: array of booleans")
{
    auto token = json::parseValue("[true,false,true]");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 3);
    CHECK(dynamic_cast<json::TrueToken *>(arr->elements[0].get()) != nullptr);
    CHECK(dynamic_cast<json::FalseToken *>(arr->elements[1].get()) != nullptr);
    CHECK(dynamic_cast<json::TrueToken *>(arr->elements[2].get()) != nullptr);
}

TEST_CASE("parseValue: array of nulls")
{
    auto token = json::parseValue("[null,null]");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 2);
    for (int i = 0; i < 2; ++i)
        CHECK(dynamic_cast<json::NullToken *>(arr->elements[i].get()) != nullptr);
}

TEST_CASE("parseValue: array of objects")
{
    auto token = json::parseValue(R"([{"a":1},{"b":2}])");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 2);
    for (int i = 0; i < 2; ++i)
        CHECK(dynamic_cast<json::ObjectToken *>(arr->elements[i].get()) != nullptr);
}

TEST_CASE("parseValue: array of arrays")
{
    auto token = json::parseValue("[[1],[2,3]]");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 2);
    for (int i = 0; i < 2; ++i)
        CHECK(dynamic_cast<json::ArrayToken *>(arr->elements[i].get()) != nullptr);
}

TEST_CASE("parseValue: mixed type array")
{
    auto token = json::parseValue(R"([1,"a",true,null,{"x":2},[3,4]])");
    CHECK(dynamic_cast<json::ArrayToken *>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken *>(token.get());
    CHECK(arr->elements.size() == 6);
    CHECK(dynamic_cast<json::NumberToken *>(arr->elements[0].get()) != nullptr);
    CHECK(dynamic_cast<json::StringToken *>(arr->elements[1].get()) != nullptr);
    CHECK(dynamic_cast<json::TrueToken *>(arr->elements[2].get()) != nullptr);
    CHECK(dynamic_cast<json::NullToken *>(arr->elements[3].get()) != nullptr);
    CHECK(dynamic_cast<json::ObjectToken *>(arr->elements[4].get()) != nullptr);
    CHECK(dynamic_cast<json::ArrayToken *>(arr->elements[5].get()) != nullptr);
}
