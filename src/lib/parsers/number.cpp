#include <string>
#include <memory>
#include <regex>
#include <stdexcept>
#include "../types/numbertoken.hpp"

using namespace std;

namespace json {
    shared_ptr<NumberToken> parseNumber(const string& s, const regex& delimiters) {
        enum class Mode {
            Scanning,
            Minus,
            Characteristic,
            CharacteristicDigit,
            DecimalPoint,
            Mantissa,
            Exponent,
            ExponentSign,
            ExponentFirstDigit,
            ExponentDigits,
            End
        };
        
        auto mode = Mode::Scanning;
        auto pos = 0;
        string value;
        regex whitespace(R"([ \n\r\t])");
        regex digits(R"(\d)");
        regex nonzeroDigits("[1-9]");
        
        while (pos < s.length() && mode != Mode::End) {
            string ch(1, s[pos]);
            
            switch (mode) {
            case Mode::Scanning:
                if (regex_search(ch, whitespace)) {
                    pos++;                    
                } else if (ch == "-") {
                    value += "-";
                    pos++;
                }
                mode = Mode::Characteristic;
                break;
                
            case Mode::Characteristic:
                if (ch == "0") {
                    value += "0";
                    pos++;
                    mode = Mode::DecimalPoint;                    
                } else if (regex_search(ch, nonzeroDigits)) {
                    value += ch;
                    pos++;
                    mode = Mode::CharacteristicDigit;
                } else {
                    throw runtime_error("Expected digit");
                }
                break;
                
            case Mode::CharacteristicDigit:
                if (regex_search(ch, digits)) {
                    value += ch;
                    pos++;
                } else if (regex_search(ch, delimiters)) {
                    mode = Mode::End;
                } else {
                    mode = Mode::DecimalPoint;
                }
                break;
                
            case Mode::DecimalPoint:
                if (ch == ".") {
                    value += ".";
                    pos++;
                    mode = Mode::Mantissa;
                } else if (regex_search(ch, delimiters)) {
                    mode = Mode::End;
                } else {
                    mode = Mode::Exponent;
                }
                break;
                
            case Mode::Mantissa:
                if (regex_search(ch, digits)) {
                    value += ch;
                    pos++;
                } else if (ch == "e" || ch == "E") {
                    mode = Mode::Exponent;
                } else if (regex_search(ch, delimiters)) {
                    mode = Mode::End;
                } else {
                    throw runtime_error("Unexpected character");
                }
                break;
                
            case Mode::Exponent:
                if (ch == "e" || ch == "E") {
                    value += "e";
                    pos++;
                    mode = Mode::ExponentSign;
                } else {
                    throw runtime_error("Expected 'e' or 'E'");
                }
                break;
                
            case Mode::ExponentSign:
                if (ch == "+" || ch == "-") {
                    value += ch;
                    pos++;
                }
                mode = Mode::ExponentFirstDigit;
                break;
                
            case Mode::ExponentFirstDigit:
                if (regex_search(ch, digits)) {
                    value += ch;
                    pos++;
                    mode = Mode::ExponentDigits;
                } else {
                    throw runtime_error("Expected digit");
                }
                break;
                
            case Mode::ExponentDigits:
                if (regex_search(ch, digits)) {
                    value += ch;
                    pos++;
                } else if (regex_search(ch, delimiters)) {
                    mode = Mode::End;
                } else {
                    throw runtime_error("Expected digit");
                }
                break;
                
            case Mode::End:
                break;

            default:
                throw runtime_error("Unexpected mode");
            }
        }
        
        switch (mode) {
        case Mode::Characteristic:
        case Mode::ExponentFirstDigit:
            throw runtime_error("Incomplete expression");
            
        default:
            break;
        }

        double number = stod(value);
        return std::make_shared<NumberToken>(pos, number);
    }
}
