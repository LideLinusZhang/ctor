#include "loadedDice.h"
#include "view.h"
#include <iostream>

using namespace std;

LoadedDice::LoadedDice(View *view) : view{view} {}

int LoadedDice::roll()
{
    int roll;

    while(true)
    {
        view->printPrompt("Input a roll between 2 and 12:");
        cin>>roll;
        if(2<=roll&&roll<=12)
            return roll;
        view->printError(ErrorType::InvalidRoll);
    }
}

