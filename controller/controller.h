#ifndef CTOR_CONTROLLER_H
#define CTOR_CONTROLLER_H

#include <iostream>

class Controller
{
protected:
    std::istream &input; // Input source, exceptions enabled.
public:
    explicit Controller(std::istream &input);
    virtual ~Controller() = 0;
};

#endif //CTOR_CONTROLLER_H
