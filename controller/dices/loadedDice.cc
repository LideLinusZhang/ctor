#include "loadedDice.h"
#include "../../view/view.h"
#include <iostream>

using namespace std;

LoadedDice::LoadedDice(View *view, std::istream& input) : Controller(input), view{view} {}

int LoadedDice::roll()
{
    int roll;

    while(true)
    {
        view->printPrompt("Input a roll between 2 and 12:");

        try {input>>roll;}
        catch (ios_base::failure&)
        {
            if(input.eof())
                throw;
            else
            {
                input.clear();
                view->printError(ErrorType::InvalidRoll);
                continue;
            }
        }

        if(2<=roll&&roll<=12)
            return roll;
        view->printError(ErrorType::InvalidRoll);
    }
}

