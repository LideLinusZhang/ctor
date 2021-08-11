#include "loadedDice.h"
#include "view.h"
#include <iostream>

using namespace std;

LoadedDice::LoadedDice(View *view, std::istream &input) : Controller(input), view{view} {}

int LoadedDice::roll()
{
    int roll;

    while (true)
    {
        view->printPrompt("Input a roll between 2 and 12:");

        try
        { input >> roll; }
        catch (ios_base::failure &)
        {
            input.clear();
            clearInput();
            view->printError(ErrorType::InvalidRoll);
            continue;
        }

        if (minRoll <= roll && roll <= maxRoll)
            return roll;
        view->printError(ErrorType::InvalidRoll);
    }
}

