#include "fairDice.h"

using namespace std;

FairDice::FairDice(int seed) : engine(seed), distribution(2, 12) {}

int FairDice::roll()
{
    return distribution(engine);
}


