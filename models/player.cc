#include "player.h"
#include "../types/buildingType.h"
#include "board.h"
#include "vertex.h"
#include "../random/random.h"
#include "../view/view.h"
#include <sstream>
#include <algorithm>

using namespace std;

Player::Player(View *view, Board *board, Color color)
        : view{view}, board{board}, color{color}
{
    for (int i = 0; i < resourceTypeCount; i++)
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
    sort(buildings.begin(),buildings.end());
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
    for (auto i : resources)
        total += i.second;
    return total;
}

Color Player::getColor() const
{
    return color;
}

void Player::loseResource()
{
    int total = getTotalResources();
    if (total < 10)
        return;

    ostringstream message;
    uniform_int_distribution<int> dist;

    int totalLost = total / 2;
    message << "Builder " << toString(color) << " loses " << totalLost
            << " resources to the geese. They lose:" << endl;
    view->printMessage(message.str());

    for (auto i : resources)
    {
        if (totalLost == 0)
            break;

        int specificLost;
        if (i.first == resources.rbegin()->first)
            specificLost = totalLost;
        else
        {
            dist.param(uniform_int_distribution<int>::param_type(0, min(i.second, totalLost)));
            specificLost = dist(Random::getRandomEngine());
        }

        if (specificLost != 0)
        {
            i.second -= specificLost;
            totalLost -= specificLost;

            message.str(string());
            message << specificLost << " " << toStringAllCaps(i.first) << endl;
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

void Player::steal(Player *other)
{
    vector<ResourceType> typesForStealing;
    // Ensure the possibility is correct.
    for (auto i : other->resources)
    {
        for (int j = 0; j < i.second; j++)
            typesForStealing.push_back(i.first);
    }

    // Select resource type
    uniform_int_distribution<int> dist(0, static_cast<int>(typesForStealing.size()) - 1);
    ResourceType typeToSteal = typesForStealing[dist(Random::getRandomEngine())];

    // Steal from other
    setResource(typeToSteal, getResource(typeToSteal) + 1);
    other->setResource(typeToSteal, other->getResource(typeToSteal) - 1);

    // Print message
    ostringstream message;
    message << "Builder " << toString(color) << " steals " << toStringAllCaps(typeToSteal)
            << " from builder " << toString(other->color) << " ." << endl;
    view->printMessage(message.str());
}

void Player::printStatus() const
{
    ostringstream message;
    message << toString(color) << " has " << points << " building points";
    for (auto i : resources)
    {
        if (i.first == ResourceType::WiFi)
            message << ", and ";
        else
            message << ", ";
        message << i.second << " " << toString(i.first);
    }
    message << "." << endl;
    view->printMessage(message.str());
}

void Player::printResidences() const
{
    ostringstream message;
    message << toString(color) << " has built:" << endl;

    for (auto i : buildings)
    {
        BuildingType type = board->getVertex(i)->getType();
        message << i << " " << toChar(type) << endl;
    }
    view->printMessage(message.str());
}



