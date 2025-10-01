#include <doctest/doctest.h>
#include <memory>
#include <regex>
#include "../../../src/lib/parsers/value.hpp"
#include "../../../src/lib/types.hpp"

TEST_CASE("parseValue: simple string")
{
    auto token = json::parseValue("\"hello\"");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "hello");
}

TEST_CASE("parseValue: empty string")
{
    auto token = json::parseValue("\"\"");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "");
}

TEST_CASE("parseValue: string with spaces")
{
    auto token = json::parseValue("\"foo bar baz\"");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "foo bar baz");
}

TEST_CASE("parseValue: string with escaped quotes")
{
    auto token = json::parseValue(R"("foo \"bar\" baz")");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "foo \"bar\" baz");
}

TEST_CASE("parseValue: string with unicode")
{
    auto token = json::parseValue(R"("\u0041\u0042\u0043")");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "ABC");
}

TEST_CASE("parseValue: string with escaped backslash")
{
    auto token = json::parseValue(R"("foo\\bar")");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "foo\\bar");
}

TEST_CASE("parseValue: string with newline")
{
    auto token = json::parseValue(R"("foo\nbar")");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "foo\nbar");
}

TEST_CASE("parseValue: string with tab")
{
    auto token = json::parseValue(R"("foo\tbar")");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "foo\tbar");
}

TEST_CASE("parseValue: string with carriage return")
{
    auto token = json::parseValue(R"("foo\rbar")");
    CHECK(dynamic_cast<json::StringToken*>(token.get()) != nullptr);
    auto* str = dynamic_cast<json::StringToken*>(token.get());
    CHECK(str->value == "foo\rbar");
}
