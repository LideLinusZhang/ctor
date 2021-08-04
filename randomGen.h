#ifndef CTOR_RANDOMGEN_H
#define CTOR_RANDOMGEN_H

#include <random>

class Random final
{
    static std::default_random_engine engine;
    Random() = default; // avoid instantiate this static class
public:
    static void init(int seed);
    static unsigned int getRandomNumber();
    static std::default_random_engine &getRandomEngine();
};

#endif //CTOR_RANDOMGEN_H
