#include "buildingType.h"
#include <stdexcept>

char toChar(BuildingType type)
{
    switch (type)
    {
        case Basement:
            return 'B';
        case House:
            return 'H';
        case Tower:
            return 'T';
        default:
            throw std::invalid_argument("type");
    }
}

BuildingType toBuildingType(char c)
{
    switch (c)
    {
        case 'B':
            return Basement;
        case 'H':
            return House;
        case 'T':
            return Tower;
        default:
            throw std::invalid_argument("type");
    }
}
