#include <string>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/stringtoken.hpp"
#include "string.hpp"

using namespace std;

namespace json {
    shared_ptr<StringToken> parseString(const string& s) {
        enum class Mode {
            Scanning,
            Char,
            EscapedChar,
            Unicode,
            End
        };
        
        auto mode = Mode::Scanning;
        auto pos = 0;
        string value;
        const regex whitespace(R"([ \n\r\t])");

        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]);
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch == "\"") {
                    value = "";
                    pos++;
                    mode = Mode::Char;
                } else {
                    throw runtime_error("expected '\"'");
                }
                break;
                
            case Mode::Char:
                if (ch == "\\") {
                    pos++;
                    mode = Mode::EscapedChar;
                } else if (ch == "\"") {
                    pos++;
                    mode = Mode::End;
                } else if (ch != "\n" && ch != "\r") {
                    value += ch;
                    pos++;
                } else {
                    throw runtime_error("unexpected character");
                }
                break;
                
            case Mode::EscapedChar:
                if (ch == "\"" || ch == "\\" || ch == "/") {
                    value += ch;
                    pos++;
                    mode = Mode::Char;
                } else if (ch == "b") {
                    value += "\b";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch == "f") {
                    value += "\f";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch == "n") {
                    value += "\n";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch == "r") {
                    value += "\r";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch == "t") {
                    value += "\t";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch == "u") {
                    pos++;
                    mode = Mode::Unicode;
                }
                break;
                
            case Mode::Unicode:
                {
                    try {
                        string slice = s.substr(pos, 4);
                        int hex = stol(slice, nullptr, 16);
                        value += static_cast<char>(hex);
                        pos += 4;
                        mode = Mode::Char;
                    } catch ([[maybe_unused]] const std::exception& invalid_argument) {
                        throw runtime_error("unexpected Unicode code");
                    }
                }
                break;
                
            case Mode::End:
                break;
                
            default:
                throw runtime_error("unexpected mode");
            }
        }

        return std::make_shared<StringToken>(pos, value);
    }
}
