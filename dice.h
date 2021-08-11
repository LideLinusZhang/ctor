#ifndef CTOR_DICE_H
#define CTOR_DICE_H

const int minRoll = 2;
const int maxRoll = 12;

class Dice
{
public:
    virtual int roll() = 0;
};

#endif //CTOR_DICE_H
