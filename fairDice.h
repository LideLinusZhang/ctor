#ifndef CTOR_FAIRDICE_H
#define CTOR_FAIRDICE_H

#include "dice.h"
#include <random>

class FairDice : public Dice
{
    std::default_random_engine engine;
    std::uniform_int_distribution<> distribution;
public:
    explicit FairDice(int seed);

    int roll() override;
};

#endif //CTOR_FAIRDICE_H
