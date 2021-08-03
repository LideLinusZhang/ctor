#include "buildingType.h"

char toChar(BuildingType type) {
    switch (type) {
        case Basement:
            return 'B';
        case House:
            return 'H';
        case Tower:
            return 'T';
    }
}

BuildingType toBuildingType(char c) {
    switch (c) {
        case 'B':
            return Basement;
        case 'H':
            return House;
        case 'T':
            return Tower;
    }
}
