#ifndef CTOR_PLAYER_H
#define CTOR_PLAYER_H

#include "color.h"
#include "resourceType.h"
#include <vector>
#include <map>

class Board;

class View;

class Player
{
    const Color color;
    std::map<ResourceType, int> resources; // index: resource type, value: resource count
    std::vector<int> buildings; // value: vertex index, in ascending order
    std::vector<int> roads;
    const View *view;
    const Board *board;
public:
    Player(View *view, Board *board, Color color);

    void addBuilding(int vertexIndex); // Add an already-built building to the player's profile.
    void addRoad(int edgeIndex);

    void setResource(ResourceType type, int count);

    int getResource(ResourceType type) const;
    int getTotalResources() const;
    int getBuildingPoint() const;
    Color getColor() const;

    void loseResource(); // If the player's total resources are less than 10, I will do nothing.

    void trade(Player *other, ResourceType give, ResourceType take); // Trade resources after other agreed.
    void steal(Player *other); // Steal other after user selected one from the list of players to steal from.

    void printStatus() const;
    void printResidences() const;

    std::string toString(); // Returns the player's data for game saving.
};

#endif //CTOR_PLAYER_H
