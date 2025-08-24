#include "doctest.h"
#include <regex>
#include <memory>
#include "../../../src/lib/parsers/value.hpp"
#include "../../../src/lib/types.hpp"

using namespace std;

TEST_CASE("parseValue: false") {
    auto token = json::parseValue("false");
    CHECK(dynamic_cast<json::FalseToken*>(token.get()) != nullptr);
}

TEST_CASE("parseValue: true") {
    auto token = json::parseValue("true");
    CHECK(dynamic_cast<json::TrueToken*>(token.get()) != nullptr);
}

TEST_CASE("parseValue: null") {
    auto token = json::parseValue("null");
    CHECK(dynamic_cast<json::NullToken*>(token.get()) != nullptr);
}

TEST_CASE("parseValue: number") {
    auto token = json::parseValue("123");
    CHECK(dynamic_cast<json::NumberToken*>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken*>(token.get());
    CHECK(num->value == 123);
}

TEST_CASE("parseValue: negative number") {
    auto token = json::parseValue("-45.67");
    CHECK(dynamic_cast<json::NumberToken*>(token.get()) != nullptr);
    auto num = dynamic_cast<json::NumberToken*>(token.get());
    CHECK(num->value == doctest::Approx(-45.67));
}

TEST_CASE("parseValue: string") {
    auto token = json::parseValue("\"hello world\"");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "hello world");
}

TEST_CASE("parseValue: array") {
    auto token = json::parseValue("[1,2,3]");
    CHECK(dynamic_cast<json::ArrayToken*>(token.get()) != nullptr);
    auto arr = dynamic_cast<json::ArrayToken*>(token.get());
    CHECK(arr->elements.size() == 3);
}

TEST_CASE("parseValue: object") {
    auto token = json::parseValue("{\"a\":1,\"b\":false}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 2);
}

TEST_CASE("parseValue: whitespace and delimiters") {
    auto token = json::parseValue("   true   ");
    CHECK(dynamic_cast<json::TrueToken*>(token.get()) != nullptr);
}
