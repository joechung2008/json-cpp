#include "doctest.h"
#include <regex>
#include <memory>
#include "../../../src/lib/parsers/value.hpp"
#include "../../../src/lib/types.hpp"

using namespace std;

TEST_CASE("parseValue: empty object") {
    auto token = json::parseValue("{}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 0);
}

TEST_CASE("parseValue: single key-value pair") {
    auto token = json::parseValue("{\"a\":1}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 1);
    CHECK(obj->members[0]->key->value == "a");
    CHECK(dynamic_cast<json::NumberToken*>(obj->members[0]->value.get()) != nullptr);
}

TEST_CASE("parseValue: multiple key-value pairs") {
    auto token = json::parseValue("{\"x\":true,\"y\":null,\"z\":\"abc\"}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 3);
    CHECK(obj->members[0]->key->value == "x");
    CHECK(dynamic_cast<json::TrueToken*>(obj->members[0]->value.get()) != nullptr);
    CHECK(obj->members[1]->key->value == "y");
    CHECK(dynamic_cast<json::NullToken*>(obj->members[1]->value.get()) != nullptr);
    CHECK(obj->members[2]->key->value == "z");
    CHECK(dynamic_cast<json::StringToken*>(obj->members[2]->value.get()) != nullptr);
}

TEST_CASE("parseValue: nested object") {
    auto token = json::parseValue("{\"outer\":{\"inner\":42}}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 1);
    CHECK(obj->members[0]->key->value == "outer");
    auto innerObj = dynamic_cast<json::ObjectToken*>(obj->members[0]->value.get());
    CHECK(innerObj != nullptr);
    CHECK(innerObj->members.size() == 1);
    CHECK(innerObj->members[0]->key->value == "inner");
    CHECK(dynamic_cast<json::NumberToken*>(innerObj->members[0]->value.get()) != nullptr);
}

TEST_CASE("parseValue: object with array value") {
    auto token = json::parseValue("{\"arr\":[1,2,3]}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 1);
    CHECK(obj->members[0]->key->value == "arr");
    CHECK(dynamic_cast<json::ArrayToken*>(obj->members[0]->value.get()) != nullptr);
}

TEST_CASE("parseValue: object with mixed value types") {
    auto token = json::parseValue("{\"num\":123,\"str\":\"abc\",\"bool\":false,\"nul\":null}");
    CHECK(dynamic_cast<json::ObjectToken*>(token.get()) != nullptr);
    auto obj = dynamic_cast<json::ObjectToken*>(token.get());
    CHECK(obj->members.size() == 4);
    CHECK(obj->members[0]->key->value == "num");
    CHECK(dynamic_cast<json::NumberToken*>(obj->members[0]->value.get()) != nullptr);
    CHECK(obj->members[1]->key->value == "str");
    CHECK(dynamic_cast<json::StringToken*>(obj->members[1]->value.get()) != nullptr);
    CHECK(obj->members[2]->key->value == "bool");
    CHECK(dynamic_cast<json::FalseToken*>(obj->members[2]->value.get()) != nullptr);
    CHECK(obj->members[3]->key->value == "nul");
    CHECK(dynamic_cast<json::NullToken*>(obj->members[3]->value.get()) != nullptr);
}
