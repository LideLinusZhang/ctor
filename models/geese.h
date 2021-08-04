#ifndef CTOR_GEESE_H
#define CTOR_GEESE_H

class Geese
{
    int position;
public:
    bool tryMoveTo(int tileIndex); // If fails, returns false. Otherwise, returns true;
    int getPosition() const;
    // Should only be used for reading game from file.
    void setPosition(int tileIndex);
};

#endif