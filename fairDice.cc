#include "fairDice.h"
#include "randomGen.h"

using namespace std;

FairDice::FairDice() : distribution(2, 12) {}

int FairDice::roll()
{
    return distribution(Random::getRandomEngine());
}
