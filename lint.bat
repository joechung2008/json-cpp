pipx run cpplint ^
  --linelength=100 ^
  --filter=-build/include_order,-runtime/references ^
  src/cli/main.cpp ^
  src/lib/parsers/array.cpp ^
  src/lib/parsers/number.cpp ^
  src/lib/parsers/object.cpp ^
  src/lib/parsers/pair.cpp ^
  src/lib/parsers/string.cpp ^
  src/lib/parsers/value.cpp ^
  src/lib/parsers/array.hpp ^
  src/lib/parsers/number.hpp ^
  src/lib/parsers/object.hpp ^
  src/lib/parsers/pair.hpp ^
  src/lib/parsers/string.hpp ^
  src/lib/parsers/value.hpp ^
  src/types.hpp ^
  src/lib/types/arraytoken.hpp ^
  src/lib/types/falsetoken.hpp ^
  src/lib/types/nulltoken.hpp ^
  src/lib/types/numbertoken.hpp ^
  src/lib/types/objecttoken.hpp ^
  src/lib/types/pairtoken.hpp ^
  src/lib/types/stringtoken.hpp ^
  src/lib/types/token.hpp ^
  src/lib/types/truetoken.hpp
