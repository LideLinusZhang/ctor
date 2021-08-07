#include "color.h"
#include <stdexcept>

using namespace std;

string toString(Color color)
{
    string str;
    switch (color)
    {
        case Blue:
            str = "Blue";
            break;
        case Red:
            str = "Red";
            break;
        case Orange:
            str = "Orange";
            break;
        case Yellow:
            str = "Yellow";
            break;
    }
    return str;
}

char toChar(Color color)
{
    char c;
    switch (color)
    {
        case Blue:
            c = 'B';
            break;
        case Red:
            c = 'R';
            break;
        case Orange:
            c = 'O';
            break;
        case Yellow:
            c = 'Y';
            break;
    }
    return c;
}

Color toColor(const string &str)
{
    if (str == "Blue")
        return Blue;
    else if (str == "Red")
        return Red;
    else if (str == "Orange")
        return Orange;
    else if (str == "Yellow")
        return Yellow;
    else
        throw invalid_argument("str");
}