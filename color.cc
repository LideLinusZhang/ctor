#include "color.h"
#include <stdexcept>

using namespace std;

string toString(Color color)
{
    switch (color)
    {
        case Blue:
            return "Blue";
        case Red:
            return "Red";
        case Orange:
            return "Orange";
        case Yellow:
            return "Yellow";
    }
}

char toChar(Color color)
{
    switch (color)
    {
        case Blue:
            return 'B';
        case Red:
            return 'R';
        case Orange:
            return 'O';
        case Yellow:
            return 'Y';
    }
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