#ifndef CTOR_RESOURCETYPE_H
#define CTOR_RESOURCETYPE_H

#define RESOURCE_TYPE_COUNT 5

enum ResourceType
{
    Brick,
    Energy,
    Glass,
    Heat,
    WiFi
};

std::string toString(ResourceType type)
{
    switch (type)
    {
        case Brick:
            return "Brick";
        case Energy:
            return "Energy";
        case Glass:
            return "Glass";
        case Heat:
            return "Heat";
        case WiFi:
            return "WiFi";
    }
}

#endif //CTOR_RESOURCETYPE_H
