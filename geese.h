#ifndef CTOR_GEESE_H
#define CTOR_GEESE_H

class Geese
{
    int position;
public:
    explicit Geese(int position);

    bool tryMoveTo(int tileIndex); // If fails, returns false. Otherwise, returns true;
    int getPosition() const;
};

#endif