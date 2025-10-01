#include <iostream>
#include <string>

#include "../lib/parsers/value.hpp"
#include "../lib/types/token.hpp"

auto main() -> int
{
    try
    {
        std::string input((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
        if (input.empty())
        {
            std::cerr << "No input provided." << '\n';
            return 1;
        }

        auto jsonValue = json::parseValue(input);
        std::cout << *jsonValue << '\n';
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}
