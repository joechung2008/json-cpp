#include <string>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/token.hpp"
#include "../types/falsetoken.hpp"
#include "../types/nulltoken.hpp"
#include "../types/truetoken.hpp"
#include "value.hpp"
#include "array.hpp"
#include "number.hpp"
#include "object.hpp"
#include "string.hpp"

using namespace std;

namespace json {
    shared_ptr<Token> parseValue(string s, regex delimiters) {
        enum class Mode {
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
        regex number(R"([\-\d])");
        regex whitespace(R"([ \n\r\t])");
        shared_ptr<Token> token = nullptr;
        
        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]), slice;

            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch.compare("[") == 0) {
                    mode = Mode::Array;
                } else if (ch.compare("f") == 0) {
                    mode = Mode::False;
                } else if (ch.compare("n") == 0) {
                    mode = Mode::Null;
                } else if (regex_search(ch, number)) {
                    mode = Mode::Number;
                } else if (ch.compare("{") == 0) {
                    mode = Mode::Object;
                } else if (ch.compare("\"") == 0) {
                    mode = Mode::String;
                } else if (ch.compare("t") == 0) {
                    mode = Mode::True;
                } else if (regex_search(ch, delimiters)) {
                    mode = Mode::End;
                } else {
                    throw runtime_error("Unexpected character");
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
                if (slice.compare("false") == 0) {
                    token = shared_ptr<FalseToken>(new FalseToken(pos + 5));
                    mode = Mode::End;
                } else {
                    throw runtime_error("Expected 'false'");
                }
                break;
                
            case Mode::Null:
                slice = s.substr(pos, 4);
                if (slice.compare("null") == 0) {
                    token = shared_ptr<NullToken>(new NullToken(pos + 4));
                    mode = Mode::End;
                } else {
                    throw runtime_error("Expected 'null'");
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
                if (slice.compare("true") == 0) {
                    token = shared_ptr<TrueToken>(new TrueToken(pos + 4));
                    mode = Mode::End;
                } else {
                    throw runtime_error("Expected 'true'");
                }
                break;
                
            case Mode::End:
                break;
                
            default:
                throw runtime_error("Unexpected mode");
            }
        }
        
        if (token == nullptr) {
            throw runtime_error("value cannot be empty");
        }
        
        return shared_ptr<Token>(token);
    }
}
