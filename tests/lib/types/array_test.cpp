#include <doctest/doctest.h>
#include <memory>
#include <sstream>
#include <vector>
#include "../../../src/lib/types.hpp"

TEST_CASE("ArrayToken writeTo empty")
{
    auto token = std::make_shared<json::ArrayToken>(0, std::vector<std::shared_ptr<json::Token>>{});
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    CHECK(oss.str() == "ArrayToken {\n    elements: []\n}");
}

TEST_CASE("ArrayToken writeTo flat")
{
    auto num1 = std::make_shared<json::NumberToken>(0, 1.0);
    auto num2 = std::make_shared<json::NumberToken>(0, 2.0);
    auto num3 = std::make_shared<json::NumberToken>(0, 3.0);
    std::vector<std::shared_ptr<json::Token>> elements = {num1, num2, num3};
    auto token = std::make_shared<json::ArrayToken>(0, elements);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    std::string expected =
        "ArrayToken {\n    elements: [\n        NumberToken { skip: 0, value: 1.0000 },\n        NumberToken { skip: "
        "0, value: 2.0000 },\n        NumberToken { skip: 0, value: 3.0000 }\n    ]\n}";
    CHECK(oss.str() == expected);
}

TEST_CASE("ArrayToken writeTo nested")
{
    auto num1 = std::make_shared<json::NumberToken>(0, 1.0);
    std::vector<std::shared_ptr<json::Token>> inner1 = {num1};
    auto arr1 = std::make_shared<json::ArrayToken>(0, inner1);

    auto num2 = std::make_shared<json::NumberToken>(0, 2.0);
    auto num3 = std::make_shared<json::NumberToken>(0, 3.0);
    std::vector<std::shared_ptr<json::Token>> inner2 = {num2, num3};
    auto arr2 = std::make_shared<json::ArrayToken>(0, inner2);

    std::vector<std::shared_ptr<json::Token>> elements = {arr1, arr2};
    auto token = std::make_shared<json::ArrayToken>(0, elements);
    std::ostringstream oss;
    token->writeTo(oss, 0, false);
    std::string expected = "ArrayToken {\n    elements: [\n        ArrayToken {\n            elements: [\n             "
                           "   NumberToken { skip: 0, value: 1.0000 }\n            ]\n        },\n        ArrayToken "
                           "{\n            elements: [\n                NumberToken { skip: 0, value: 2.0000 },\n      "
                           "          NumberToken { skip: 0, value: 3.0000 }\n            ]\n        }\n    ]\n}";
    CHECK(oss.str() == expected);
}