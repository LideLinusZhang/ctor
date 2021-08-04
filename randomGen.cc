#include "randomGen.h"

using namespace std;

default_random_engine Random::engine;

void Random::init(int seed)
{
    Random::engine.seed(seed);
}

unsigned int Random::getRandomNumber()
{
    return Random::engine();
}

std::default_random_engine &Random::getRandomEngine()
{
    return Random::engine;
}
