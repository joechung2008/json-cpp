#include <iostream>
#include <string>

#include "../lib/parsers/value.hpp"
#include "../lib/types/token.hpp"

int main()
{
    try
    {
        std::string input((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
        if (input.empty())
        {
            std::cerr << "No input provided." << std::endl;
            return 1;
        }

        auto jsonValue = json::parseValue(input);
        std::cout << *jsonValue << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
