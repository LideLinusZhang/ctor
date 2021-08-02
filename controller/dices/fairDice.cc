#include "fairDice.h"
#include "../../random/random.h"

using namespace std;

FairDice::FairDice() : distribution(2, 12) {}

int FairDice::roll()
{
    return distribution(Random::getRandomEngine());
}
