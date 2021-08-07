#include "resourceType.h"
#include <stdexcept>

using namespace std;

string toStringAllCaps(ResourceType type)
{
    string str;
    switch (type)
    {
        case Brick:
            str = "BRICK";
            break;
        case Energy:
            str = "ENERGY";
            break;
        case Glass:
            str = "GLASS";
            break;
        case Heat:
            str = "HEAT";
            break;
        case WiFi:
            str = "WIFI";
            break;
        case Park:
            str = "PARK";
            break;
    }
    return str;
}

string toString(ResourceType type)
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
        default:
            throw invalid_argument("type");
    }
}

ResourceType toResourceType(const string &str)
{
    if (str == "BRICK")
        return Brick;
    else if (str == "ENERGY")
        return Energy;
    else if (str == "GLASS")
        return Glass;
    else if (str == "HEAT")
        return Heat;
    else if (str == "WIFI")
        return WiFi;
    else
        throw invalid_argument("str");
}

