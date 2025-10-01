#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include "../types/arraytoken.hpp"
#include "../types/token.hpp"
#include "value.hpp"

namespace json
{
    std::shared_ptr<ArrayToken> parseArray(const std::string &s)
    {
        enum class Mode
        {
            Scanning,
            Element,
            Comma,
            End
        };

        auto mode = Mode::Scanning;
        auto pos = 0;
        const std::regex delimiters(R"([ \n\r\t\],])");
        const std::regex whitespace(R"([ \n\r\t])");
        auto pElements = std::make_shared<std::vector<std::shared_ptr<Token>>>();

        while (pos < s.length() && mode != Mode::End)
        {
            std::string ch(1, s[pos]);

            switch (mode)
            {
            case Mode::Scanning:
                if (std::regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == "[")
                {
                    pos++;
                    mode = Mode::Element;
                }
                else
                {
                    throw std::runtime_error("Expected '['");
                }
                break;

            case Mode::Element:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == "]")
                {
                    if (!pElements->empty())
                    {
                        throw std::runtime_error("Unexpected ','");
                    }

                    pos++;
                    mode = Mode::End;
                }
                else
                {
                    std::string slice = s.substr(pos);
                    std::shared_ptr<Token> element = parseValue(slice, delimiters);
                    pElements->push_back(element);
                    pos += element->skip;
                    mode = Mode::Comma;
                }
                break;

            case Mode::Comma:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == ",")
                {
                    pos++;
                    mode = Mode::Element;
                }
                else if (ch == "]")
                {
                    pos++;
                    mode = Mode::End;
                }
                else
                {
                    throw std::runtime_error("Expected ',' or ']'");
                }
                break;

            case Mode::End:
                break;

            default:
                throw std::runtime_error("Unexpected mode");
            }
        }

        return std::make_shared<ArrayToken>(pos, *pElements);
    }
}
