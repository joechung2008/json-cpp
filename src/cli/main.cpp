#include <iostream>
#include <string>
#include "../lib/parsers/value.hpp"
#include "../lib/types/token.hpp"

using namespace json;
using namespace std;

int main()
{
    try
    {
        string s((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
        auto json = parseValue(s);
        cout << *json << endl;
    }
    catch (exception &ex)
    {
        cerr << ex.what() << endl;
    }

    return 0;
}
