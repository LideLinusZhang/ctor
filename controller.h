#ifndef CTOR_CONTROLLER_H
#define CTOR_CONTROLLER_H

#include <iostream>

class Controller
{
protected:
    std::istream &input; // Input source, exceptions enabled.
public:
    explicit Controller(std::istream &input);
};

#endif //CTOR_CONTROLLER_H
