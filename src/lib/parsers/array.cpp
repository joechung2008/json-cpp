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
    shared_ptr<ArrayToken> parseArray(string s) {
        enum class Mode {
            Scanning,
            Element,
            Comma,
            End
        };
        
        auto mode = Mode::Scanning;
        auto pos = 0;
        regex whitespace(R"([ \n\r\t])");
        auto pelements = shared_ptr<vector<shared_ptr<Token>>>(new vector<shared_ptr<Token>>());

        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]);
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch.compare("[") == 0) {
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
                    if (pelements->size() > 0) {
                        throw runtime_error("Unexpected ','");
                    }
                    
                    pos++;
                    mode = Mode::End;
                } else {
                    string slice = s.substr(pos);
                    shared_ptr<Token> element = parseValue(slice, regex(R"([ \n\r\t\],])"));
                    pelements->push_back(element);
                    pos += element->skip;
                    mode = Mode::Comma;
                }
                break;
                
            case Mode::Comma:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch.compare(",") == 0) {
                    pos++;
                    mode = Mode::Element;
                } else if (ch.compare("]") == 0) {
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
        
        return shared_ptr<ArrayToken>(new ArrayToken(pos, *pelements));
    }
}
