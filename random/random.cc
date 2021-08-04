#include "random.h"

using namespace std;

void Random::init(int seed)
{
    engine.seed(seed);
}

unsigned int Random::getRandomNumber()
{
    return engine();
}

std::default_random_engine &Random::getRandomEngine()
{
    return engine;
}
