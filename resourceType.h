#ifndef CTOR_RESOURCETYPE_H
#define CTOR_RESOURCETYPE_H

#include <string>

const int resourceTypeCount = 5;

enum ResourceType
{
    Brick,
    Energy,
    Glass,
    Heat,
    WiFi
};

std::string toStringAllCaps(ResourceType type)
{
    switch (type)
    {
        case Brick:
            return "BRICK";
        case Energy:
            return "ENERGY";
        case Glass:
            return "GLASS";
        case Heat:
            return "HEAT";
        case WiFi:
            return "WIFI";
    }
}

std::string toString(ResourceType type)
{
    switch (type)
    {
        case Brick:
            return "brick";
        case Energy:
            return "energy";
        case Glass:
            return "glass";
        case Heat:
            return "heat";
        case WiFi:
            return "WiFi";
    }
}

#endif //CTOR_RESOURCETYPE_H
