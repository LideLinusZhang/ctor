#ifndef CTOR_LOADEDDICE_H
#define CTOR_LOADEDDICE_H

#include "../controller.h"
#include "dice.h"
#include <iostream>

class View;

class LoadedDice : public Dice, public Controller
{
    View *view;
public:
    explicit LoadedDice(View *view, std::istream &input);

    int roll() override;
};

#endif //CTOR_LOADEDDICE_H
