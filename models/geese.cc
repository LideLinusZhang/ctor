#include "geese.h"

bool Geese::tryMoveTo(int tileIndex){
    if(tileIndex>=0 && tileIndex<=18 && tileIndex!=position){
        position = tileIndex;
        return true;
    }
    return false;
}

inline int Geese::getPosition() const{
    return position;
}

void Geese::setPosition(int tileIndex)
{
    position=tileIndex;
}
