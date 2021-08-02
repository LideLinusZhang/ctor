#include "vertex.h"
#include "view.h"
#include "board.h"
#include "player.h"

Vertex::Vertex(View* view, std::vector<int> edgeIndices)
        :view(view), edgeIndices(edgeIndices)
{
    owner = nullptr;
    type = BuildingType::None;
    board = nullptr;
}

Vertex::Vertex(View* view, Player* owner, BuildingType type, std::vector<int> edgeIndices)
        :view(view), owner(owner), type(type), edgeIndices(edgeIndices)
{
    board = nullptr;
}

void Vertex::setBoard(Board *b){
    board = b;
}

inline Player *Vertex::getOwner() const{
    return owner;
}

inline BuildingType Vertex::getType() const{
    return type;
}

void Vertex::build(Player *player){
    if(type!=BuildingType::None)
    {
        return;
    }
    //cost one BRICK, one ENERGY, one GLASS, and one WIFI
    int brick_num = player->getResource(ResourceType::Brick);
    int energy_num = player->getResource(ResourceType::Energy);
    int glass_num = player->getResource(ResourceType::Glass);
    int wifi_num = player->getResource(ResourceType::WiFi);

    if (brick_num>=1 && energy_num>=1 && glass_num>=1 && wifi_num>=1)
    {
        owner = player;
        type = BuildingType::Basement;
        player->setResource(ResourceType::Brick, --brick_num);
        player->setResource(ResourceType::Energy, --energy_num);
        player->setResource(ResourceType::Glass, --glass_num);
        player->setResource(ResourceType::WiFi, --wifi_num);

    }
}

void Vertex::improve(Player *player){
    if(BuildingType::None==type || BuildingType::Tower==type || player!=owner)
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }

    if(BuildingType::Basement == type)
    {
        //cost two GLASS, and three HEAT
        int glass_num = player->getResource(ResourceType::Glass);
        int heat_num = player->getResource(ResourceType::Heat);
        if (glass_num>=2 &&heat_num>=3)
        {
            type = BuildingType::House;
            player->setResource(ResourceType::Glass, glass_num-2);
            player->setResource(ResourceType::Heat, heat_num-3);
        }
    }
    else if(BuildingType::House == type)
    {
        //cost three BRICK, two ENERGY, two GLASS, one WIFI, and two HEAT
        int brick_num = player->getResource(ResourceType::Brick);
        int energy_num = player->getResource(ResourceType::Energy);
        int glass_num = player->getResource(ResourceType::Glass);
        int wifi_num = player->getResource(ResourceType::WiFi);
        int heat_num = player->getResource(ResourceType::Heat);

        if(brick_num>=3 && energy_num>=2 && glass_num>=2 && wifi_num>=1 && heat_num>=2)
        {
            type = BuildingType::Tower;
            player->setResource(ResourceType::Brick, brick_num-3);
            player->setResource(ResourceType::Energy, energy_num-2);
            player->setResource(ResourceType::Glass, glass_num-2);
            player->setResource(ResourceType::WiFi, wifi_num-1);
            player->setResource(ResourceType::Heat, heat_num-2);

        }
    }


}

std::vector<int> Vertex::getedgeIndices() const{
    return edgeIndices;
}
