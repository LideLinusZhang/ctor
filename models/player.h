#ifndef CTOR_PLAYER_H
#define CTOR_PLAYER_H

#include "../types/color.h"
#include "../types/resourceType.h"
#include <vector>
#include <map>

class Board;
class View;

class Player
{
    Color color;
    int points=0;
    std::map<ResourceType,int> resources; // index: resource type, value: resource count
    std::vector<int> buildings; // value: vertex index, in ascending order
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
    Color getColor() const;

    void loseResource(); // If the player's total resources are less than 10, I will do nothing.

    void trade(Player* other, ResourceType give, ResourceType take); // Trade resources after other agreed.
    void steal(Player* other); // Steal other after user selected one from the list of players to steal from.

    void printStatus() const;
    void printResidences() const;
};

#endif //CTOR_PLAYER_H
