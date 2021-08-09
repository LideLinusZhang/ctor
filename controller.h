#ifndef CTOR_CONTROLLER_H
#define CTOR_CONTROLLER_H

#include <iostream>

class Controller
{
protected:
    std::istream &input; // Input source, exceptions enabled.

    // Clear the rest of the current line in input.
    // Can be used for clearing invalid inputs.
    void clearInput();
public:
    explicit Controller(std::istream &input);
    virtual ~Controller() = 0;
};

#endif //CTOR_CONTROLLER_H
