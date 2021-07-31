#ifndef CTOR_BUILDINGTYPE_H
#define CTOR_BUILDINGTYPE_H

enum BuildingType
{
    None,
    Basement,
    House,
    Tower
};

std::string toString(BuildingType type)
{
    switch (type)
    {
        case Basement:
            return "B";
        case House:
            return "H";
        case Tower:
            return "T";
        default:
            return {};
    }
}

#endif //CTOR_BUILDINGTYPE_H
