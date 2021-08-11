#ifndef CTOR_RESOURCETYPE_H
#define CTOR_RESOURCETYPE_H

#include <string>

const int totalResourceTypes = 5;

enum ResourceType
{
    Brick,
    Energy,
    Glass,
    Heat,
    WiFi,
    Park
};

std::string toStringAllCaps(ResourceType type);
std::string toString(ResourceType type);
// If str is unrecognized, throw invalid_argument.
ResourceType toResourceType(const std::string &str);


#endif //CTOR_RESOURCETYPE_H
