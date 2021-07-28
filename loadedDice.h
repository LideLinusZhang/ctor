#ifndef CTOR_LOADEDDICE_H
#define CTOR_LOADEDDICE_H

#include "dice.h"

class View;

class LoadedDice : public Dice
{
    View* view;
public:
    explicit LoadedDice(View* view);

    int roll() override;
};

#endif //CTOR_LOADEDDICE_H
