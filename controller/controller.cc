#include "controller.h"

using namespace std;

Controller::Controller(istream &input) : input{input}
{
    input.exceptions(ios::eofbit | ios::failbit);
}