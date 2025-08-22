#include <string>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/stringtoken.hpp"
#include "string.hpp"

using namespace std;

namespace json {
    shared_ptr<StringToken> parseString(string s) {
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
        regex whitespace(R"([ \n\r\t])");

        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]);
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch.compare("\"") == 0) {
                    value = "";
                    pos++;
                    mode = Mode::Char;
                } else {
                    throw runtime_error("expected '\"'");
                }
                break;
                
            case Mode::Char:
                if (ch.compare("\\") == 0) {
                    pos++;
                    mode = Mode::EscapedChar;
                } else if (ch.compare("\"") == 0) {
                    pos++;
                    mode = Mode::End;
                } else if (ch.compare("\n") != 0 && ch.compare("\r") != 0) {
                    value += ch;
                    pos++;
                } else {
                    throw runtime_error("unexpected character");
                }
                break;
                
            case Mode::EscapedChar:
                if (ch.compare("\"") == 0 || ch.compare("\\") == 0 || ch.compare("/") == 0) {
                    value += ch;
                    pos++;
                    mode = Mode::Char;
                } else if (ch.compare("b") == 0) {
                    value += "\b";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch.compare("f") == 0) {
                    value += "\f";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch.compare("n") == 0) {
                    value += "\n";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch.compare("r") == 0) {
                    value += "\r";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch.compare("t") == 0) {
                    value += "\t";
                    pos++;
                    mode = Mode::Char;                    
                } else if (ch.compare("u") == 0) {
                    pos++;
                    mode = Mode::Unicode;
                }
                break;
                
            case Mode::Unicode:
                {
                    try {
                        string slice = s.substr(pos, 4);
                        int hex = stol(slice, nullptr, 16);
                        value += (char)hex;
                        pos += 4;
                        mode = Mode::Char;
                    } catch (invalid_argument) {
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

        return shared_ptr<StringToken>(new StringToken(pos, value));
    }
}
