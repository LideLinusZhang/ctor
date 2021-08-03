#ifndef CTOR_BUILDINGTYPE_H
#define CTOR_BUILDINGTYPE_H

enum BuildingType {
    None,
    Basement,
    House,
    Tower
};

char toChar(BuildingType type);
BuildingType toBuildingType(char c);

#endif //CTOR_BUILDINGTYPE_H
