#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/token.hpp"
#include "../types/arraytoken.hpp"
#include "value.hpp"

using namespace std;

namespace json {
    shared_ptr<ArrayToken> parseArray(const string& s) {
        enum class Mode {
            Scanning,
            Element,
            Comma,
            End
        };
        
        auto mode = Mode::Scanning;
        auto pos = 0;
        const regex whitespace(R"([ \n\r\t])");
        auto pElements = std::make_shared<vector<shared_ptr<Token>>>();

        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]);
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch == "[") {
                    pos++;
                    mode = Mode::Element;
                } else {
                    throw runtime_error("Expected '['");
                }
                break;
                
            case Mode::Element:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch == "]") {
                    if (!pElements->empty()) {
                        throw runtime_error("Unexpected ','");
                    }
                    
                    pos++;
                    mode = Mode::End;
                } else {
                    string slice = s.substr(pos);
                    shared_ptr<Token> element = parseValue(slice, regex(R"([ \n\r\t\],])"));
                    pElements->push_back(element);
                    pos += element->skip;
                    mode = Mode::Comma;
                }
                break;
                
            case Mode::Comma:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch == ",") {
                    pos++;
                    mode = Mode::Element;
                } else if (ch == "]") {
                    pos++;
                    mode = Mode::End;
                } else {
                    throw runtime_error("Expected ',' or ']'");
                }
                break;

            case Mode::End:
                break;

            default:
                throw runtime_error("Unexpected mode");
            }
        }
        
        return std::make_shared<ArrayToken>(pos, *pElements);
    }
}
