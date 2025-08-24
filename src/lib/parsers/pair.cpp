#include <string>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/pairtoken.hpp"
#include "../types/stringtoken.hpp"
#include "../types/token.hpp"
#include "pair.hpp"
#include "string.hpp"
#include "value.hpp"

using namespace std;

namespace json {
    shared_ptr<PairToken> parsePair(const string& s, const regex& delimiters) {
        enum class Mode {
            Scanning,
            Key,
            Colon,
            Value,
            End
        };
        
        auto mode = Mode::Scanning;
        auto pos = 0;
        const regex whitespace(R"([ \n\r\t])");
        shared_ptr<StringToken> key;
        shared_ptr<Token> value;
        
        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]), slice;
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else {
                    mode = Mode::Key;
                }
                break;
                
            case Mode::Key:
                slice = s.substr(pos);
                key = parseString(slice);
                pos += key->skip;
                mode = Mode::Colon;
                break;

            case Mode::Colon:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch == ":") {
                    pos++;
                    mode = Mode::Value;
                } else {
                    throw runtime_error("Expected ':'");
                }
                break;
                
            case Mode::Value:
                slice = s.substr(pos);
                value = parseValue(slice, delimiters);
                pos += value->skip;
                mode = Mode::End;
                break;

            case Mode::End:
                break;
                
            default:
                throw runtime_error("Unexpected mode");
            }
        }
        
        return std::make_shared<PairToken>(pos, key, value);
    }
}
