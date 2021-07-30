#include "player.h"
#include "buildingType.h"
#include "board.h"
#include "vertex.h"
#include "random.h"
#include "view.h"
#include <sstream>

using namespace std;

Player::Player(View *view, Board *board, Color color)
        : view{view}, board{board}, color{color}
{
    for (int i = 0; i < RESOURCE_TYPE_COUNT; i++)
        resources.insert({static_cast<ResourceType>(i), 0});
}

Player::Player(View *view, Board *board, Color color, int points, std::map<ResourceType, int> resources,
               std::vector<int> buildings)
        : view{view}, board{board}, color{color}, points{points}, resources{move(resources)}, buildings{move(buildings)}
{
}

void Player::addBuilding(int vertexIndex)
{
    buildings.emplace_back(vertexIndex);
    points++;
}

void Player::setResource(ResourceType type, int count)
{
    resources[type] = count;
}

int Player::getResource(ResourceType type) const
{
    return resources.at(type);
}

int Player::getBuildingPoint() const
{
    return points;
}

int Player::getTotalResources() const
{
    int total = 0;
    for(auto i : resources)
        total+=i.second;
    return total;
}

void Player::loseResource()
{
    int total = getTotalResources();
    if (total < 10)
        return;

    ostringstream message;
    uniform_int_distribution<int> dist;

    int totalLost = total / 2;
    message<<"Builder "<<toString(color)<<" loses "<<totalLost<<" resources to the geese. They lose:";
    view->printMessage(message.str());

    for(auto i : resources)
    {
        if(totalLost == 0)
            break;

        int specificLost;
        if(i.first == resources.rbegin()->first)
            specificLost = totalLost;
        else
        {
            dist.param(uniform_int_distribution<int>::param_type(0, min(i.second,totalLost)));
            specificLost = dist(Random::getRandomEngine());
        }

        if(specificLost!=0)
        {
            i.second-=specificLost;
            totalLost-=specificLost;

            message.str(string());
            message<<specificLost<<" "<<toString(i.first);
            view->printMessage(message.str());
        }
    }
}

void Player::trade(Player *other, ResourceType give, ResourceType take)
{
    setResource(give, getResource(give) - 1);
    other->setResource(give, other->getResource(give) + 1);

    setResource(take, getResource(take) + 1);
    other->setResource(take, other->getResource(take) - 1);
}

