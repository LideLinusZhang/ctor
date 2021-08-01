#include "view.h"
#include <iostream>

using namespace std;

View::View(ostream &output, ostream &error) : output{output}, error{error} {}

void View::printMessage(const string &message) const
{
    output << message << endl;
}

void View::printPrompt(const string &prompt) const
{
    output << prompt << endl << "¿ ";
}

void View::printError(ErrorType type) const
{
    switch (type)
    {
        case ErrorType::InvalidBuildOrImprove:
            error << "You cannot build here." << endl;
            break;
        case ErrorType::InvalidRoll:
            error << "Invalid roll." << endl;
            break;
        case ErrorType::InvalidCommand:
            error << "Invalid command." << endl;
            break;
        case ErrorType::InsufficientResource:
            error << "You do not have enough resources." << endl;
            break;
        case ErrorType::InvalidInput:
            error << "Invalid input." << endl;
    }
}


