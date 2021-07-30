#ifndef CTOR_COLOR_H
#define CTOR_COLOR_H

enum Color
{
    Blue,
    Red,
    Orange,
    Yellow
};

std::string toString(Color color)
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

#endif //CTOR_COLOR_H
