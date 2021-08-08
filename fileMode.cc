#include "fileMode.h"
#include "adjacencyTables.h"
#include "resourceType.h"
#include "tile.h"

using namespace std;

FileMode::FileMode(std::istream &file) : file{file}
{
}

int FileMode::createLayout(Board *board)
{
    std::vector<std::shared_ptr<Tile>> tiles;
    int resource = 0;
    int value = 0;
    ResourceType type;

    int parkIndex;

    for (int i = 0; i < totalTiles; i++)
    {
        file >> resource;
        file >> value;
        switch (resource)
        {
            case 0:
                type = ResourceType::Brick;
                break;
            case 1:
                type = ResourceType::Energy;
                break;
            case 2:
                type = ResourceType::Glass;
                break;
            case 3:
                type = ResourceType::Heat;
                break;
            case 4:
                type = ResourceType::WiFi;
                break;
            case 5:
                type = ResourceType::Park;
                parkIndex = i;
                break;
        }

        vector<int> vertices = vector<int>(tileSurroundingVertexIdx[i],
                                           tileSurroundingVertexIdx[i] + tileSurroundingVertexNum);
        tiles.emplace_back(std::make_shared<Tile>(board, vertices, type, i, value));
    }

    setLayout(board, tiles);

    return parkIndex;
}
