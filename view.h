#ifndef CTOR_VIEW_H
#define CTOR_VIEW_H

#include "errorType.h"
#include <string>
#include <iostream>

class Board;

class View
{
    std::ostream &output;
    std::ostream &error;
public:
    explicit View(std::ostream &output = std::cout, std::ostream &error = std::cerr);

    void printBoard(Board *board) const;
    void printError(ErrorType type) const;
    // Use this to print a prompt that requires a user response.
    // A newline and the prompt symbol '¿' will be printed.
    void printPrompt(const std::string &prompt) const;
    // Use this to print a message that does not require a user response.
    // A newline will NOT be printed at the end.
    void printMessage(const std::string &message) const;
};

#endif //CTOR_VIEW_H
