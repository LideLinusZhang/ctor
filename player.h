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
    Color color;
    int points=0;
    std::map<ResourceType,int> resources; // index: resource type, value: resource count
    std::vector<int> buildings; // value: vertex index
    View* view;
    Board* board;

    int getTotalResources() const;
public:
    Player(View* view, Board* board, Color color);
    Player(View* view, Board* board, Color color, int points, std::map<ResourceType,int> resources,
           std::vector<int> buildings);

    void addBuilding(int vertexIndex); // Add an already-built building to the player's profile.

    void setResource(ResourceType type, int count);

    int getResource(ResourceType type) const;
    int getBuildingPoint() const;

    void loseResource();

    void trade(Player* other, ResourceType give, ResourceType take); // Trade resources after other agreed.
    void steal(Player* other);

    void printStatus() const;
    void printResidences() const;
};

#endif //CTOR_PLAYER_H
