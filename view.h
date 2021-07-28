#ifndef CTOR_VIEW_H
#define CTOR_VIEW_H

#include "errorType.h"

class Board;

class View
{
public:
    void printBoard(Board * board) const;
    void printError(ErrorType type) const;
    // Use this to print a prompt that requires a user response. The symbol '¿' will be printed.
    void printPrompt(std::string prompt) const;
    // Use this to print a message that does not require a user response.
    void printMessage(std::string message) const;
};

#endif //CTOR_VIEW_H
