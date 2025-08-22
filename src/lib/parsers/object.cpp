#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/objecttoken.hpp"
#include "../types/pairtoken.hpp"
#include "object.hpp"
#include "pair.hpp"

using namespace std;

namespace json {
    shared_ptr<ObjectToken> parseObject(string s) {
        enum class Mode {
            Scanning,
            LeftBrace,
            Pair,
            Delimiter,
            End
        };
        
        auto mode = Mode::Scanning;
        auto pos = 0;
        regex whitespace(R"([ \n\r\t])");
        auto pmembers = shared_ptr<vector<shared_ptr<PairToken>>>(new vector<shared_ptr<PairToken>>());
        
        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]);
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch.compare("{") == 0) {
                    pos++;
                    mode = Mode::Pair;
                } else {
                    throw runtime_error("Expected '{'");
                }
                break;

            case Mode::Pair:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch == "}") {
                    if (pmembers->size() > 0) {
                        throw runtime_error("Unexpected ','");
                    }

                    pos++;
                    mode = Mode::End;
                } else {
                    string slice = s.substr(pos);
                    shared_ptr<PairToken> member = parsePair(slice, regex(R"([ \n\r\t,\}])"));
                    pmembers->push_back(member);
                    pos += member->skip;
                    mode = Mode::Delimiter;
                }
                break;
                
            case Mode::Delimiter:
                if (regex_search(ch, whitespace)) {
                    pos++;
                } else if (ch.compare(",") == 0) {
                    pos++;
                    mode = Mode::Pair;
                } else if (ch.compare("}") == 0) {
                    pos++;
                    mode = Mode::End;
                } else {
                    throw runtime_error("Expected ',' or '}'");
                }
                break;

            case Mode::End:
                break;
                
            default:
                throw runtime_error("Unexpected mode");
            }
        }
        
        return shared_ptr<ObjectToken>(new ObjectToken(pos, *pmembers));
    }
}
