#include <doctest/doctest.h>
#include <memory>
#include <sstream>
#include <vector>
#include "../../../src/lib/types.hpp"

TEST_CASE("ObjectToken writeTo empty")
{
    auto token = std::make_shared<json::ObjectToken>(0, std::vector<std::shared_ptr<json::PairToken>>{});
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "ObjectToken {\n    members: []\n}");
}

TEST_CASE("ObjectToken writeTo flat")
{
    auto key1 = std::make_shared<json::StringToken>(0, "a");
    auto val1 = std::make_shared<json::NumberToken>(0, 1.0);
    auto pair1 = std::make_shared<json::PairToken>(0, key1, val1);

    auto key2 = std::make_shared<json::StringToken>(0, "b");
    auto val2 = std::make_shared<json::NumberToken>(0, 2.0);
    auto pair2 = std::make_shared<json::PairToken>(0, key2, val2);

    std::vector<std::shared_ptr<json::PairToken>> members = {pair1, pair2};
    auto token = std::make_shared<json::ObjectToken>(0, members);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    std::string expected = "ObjectToken {\n    members: [\n        PairToken {\n            key: StringToken { skip: "
                           "0, value: \"a\" },\n            value: NumberToken { skip: 0, value: 1.0000 }\n        "
                           "},\n        PairToken {\n            key: StringToken { skip: 0, value: \"b\" },\n         "
                           "   value: NumberToken { skip: 0, value: 2.0000 }\n        }\n    ]\n}";
    CHECK(oss.str() == expected);
}

TEST_CASE("ObjectToken writeTo nested")
{
    auto key1 = std::make_shared<json::StringToken>(0, "x");
    auto inner_key = std::make_shared<json::StringToken>(0, "y");
    auto inner_val = std::make_shared<json::NumberToken>(0, 3.0);
    auto inner_pair = std::make_shared<json::PairToken>(0, inner_key, inner_val);
    std::vector<std::shared_ptr<json::PairToken>> inner_members = {inner_pair};
    auto val1 = std::make_shared<json::ObjectToken>(0, inner_members);
    auto pair1 = std::make_shared<json::PairToken>(0, key1, val1);

    std::vector<std::shared_ptr<json::PairToken>> members = {pair1};
    auto token = std::make_shared<json::ObjectToken>(0, members);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    std::string expected =
        "ObjectToken {\n    members: [\n        PairToken {\n            key: StringToken { skip: 0, value: \"x\" },\n "
        "           value: ObjectToken {\n                members: [\n                    PairToken {\n                "
        "        key: StringToken { skip: 0, value: \"y\" },\n                        value: NumberToken { skip: 0, "
        "value: 3.0000 }\n                    }\n                ]\n            }\n        }\n    ]\n}";
    CHECK(oss.str() == expected);
}