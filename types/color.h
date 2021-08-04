#ifndef CTOR_COLOR_H
#define CTOR_COLOR_H

#include <string>

enum Color
{
    Blue,
    Red,
    Orange,
    Yellow
};

std::string toString(Color color);
char toChar(Color color);
// If str is unrecognized, throw invalid_argument.
Color toColor(const std::string &str);

#endif //CTOR_COLOR_H
