#ifndef CTOR_FAIRDICE_H
#define CTOR_FAIRDICE_H

#include "dice.h"
#include <random>

class FairDice : public Dice
{
    std::uniform_int_distribution<> distribution;
public:
    FairDice();

    int roll() override;
};

#endif //CTOR_FAIRDICE_H
