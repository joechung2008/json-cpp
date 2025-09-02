#include <memory>
#include <string>
#include <regex>
#include <stdexcept>
#include "../types.hpp"
#include "array.hpp"
#include "number.hpp"
#include "object.hpp"
#include "string.hpp"
#include "value.hpp"

namespace json
{
    std::shared_ptr<Token> parseValue(const std::string &s, const std::regex &delimiters)
    {
        enum class Mode
        {
            Scanning,
            Array,
            False,
            Null,
            Number,
            Object,
            String,
            True,
            End
        };

        auto mode = Mode::Scanning;
        auto pos = 0;
        const std::regex number(R"([\-\d])");
        const std::regex whitespace(R"([ \n\r\t])");
        std::shared_ptr<Token> token = nullptr;

        while (pos < s.length() && mode != Mode::End)
        {
            std::string ch(1, s[pos]), slice;

            switch (mode)
            {
            case Mode::Scanning:
                if (regex_search(ch, whitespace))
                {
                    pos++;
                }
                else if (ch == "[")
                {
                    mode = Mode::Array;
                }
                else if (ch == "f")
                {
                    mode = Mode::False;
                }
                else if (ch == "n")
                {
                    mode = Mode::Null;
                }
                else if (regex_search(ch, number))
                {
                    mode = Mode::Number;
                }
                else if (ch == "{")
                {
                    mode = Mode::Object;
                }
                else if (ch == "\"")
                {
                    mode = Mode::String;
                }
                else if (ch == "t")
                {
                    mode = Mode::True;
                }
                else if (regex_search(ch, delimiters))
                {
                    mode = Mode::End;
                }
                else
                {
                    throw std::runtime_error("Unexpected character");
                }
                break;

            case Mode::Array:
                slice = s.substr(pos);
                token = json::parseArray(slice);
                token->skip += pos;
                mode = Mode::End;
                break;

            case Mode::False:
                slice = s.substr(pos, 5);
                if (slice == "false")
                {
                    token = std::make_shared<FalseToken>(pos + 5);
                    mode = Mode::End;
                }
                else
                {
                    throw std::runtime_error("Expected 'false'");
                }
                break;

            case Mode::Null:
                slice = s.substr(pos, 4);
                if (slice == "null")
                {
                    token = std::make_shared<NullToken>(pos + 4);
                    mode = Mode::End;
                }
                else
                {
                    throw std::runtime_error("Expected 'null'");
                }
                break;

            case Mode::Number:
                slice = s.substr(pos);
                token = json::parseNumber(slice, delimiters);
                token->skip += pos;
                mode = Mode::End;
                break;

            case Mode::Object:
                slice = s.substr(pos);
                token = json::parseObject(slice);
                token->skip += pos;
                mode = Mode::End;
                break;

            case Mode::String:
                slice = s.substr(pos);
                token = json::parseString(slice);
                token->skip += pos;
                mode = Mode::End;
                break;

            case Mode::True:
                slice = s.substr(pos, 4);
                if (slice == "true")
                {
                    token = std::make_shared<TrueToken>(pos + 4);
                    mode = Mode::End;
                }
                else
                {
                    throw std::runtime_error("Expected 'true'");
                }
                break;

            case Mode::End:
                break;

            default:
                throw std::runtime_error("Unexpected mode");
            }
        }

        if (token == nullptr)
        {
            throw std::runtime_error("value cannot be empty");
        }

        return token;
    }
}
