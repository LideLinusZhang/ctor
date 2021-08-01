#include "resourceType.h"
#include <stdexcept>

using namespace std;

string toStringAllCaps(ResourceType type)
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
    }
}

ResourceType toResourceType(const string &str)
{
    if(str == "BRICK")
        return Brick;
    else if (str=="ENERGY")
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

