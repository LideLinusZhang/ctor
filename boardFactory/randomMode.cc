#include "../random/random.h"
#include "../models/board.h"
#include "randomMode.h"
#include "../adjacencyTables.h"

using namespace std;

vector<ResourceType> RandomMode::shuffleResource()
{
    vector<ResourceType> resources(totalTiles);
    for (int i = 0; i < 3; i++)
    {
        resources.push_back(ResourceType::WiFi);
    }
    for (int i = 0; i < 3; i++)
    {
        resources.push_back(ResourceType::Heat);
    }
    for (int i = 0; i < 3; i++)
    {
        resources.push_back(ResourceType::Brick);
    }
    for (int i = 0; i < 3; i++)
    {
        resources.push_back(ResourceType::Glass);
    }
    for (int i = 0; i < 3; i++)
    {
        resources.push_back(ResourceType::Energy);
    }
    resources.push_back(ResourceType::Park);
    auto rng = Random::getRandomEngine();
    shuffle(resources.begin(), resources.end(), rng);
    return resources;
}

vector<int> RandomMode::shuffleValues(std::vector<ResourceType> resources)
{
    vector<int> values;
    for (int i = 2; i < 13; i++)
    {
        values.push_back(i);
        if (i != 2 && i != 12 && i != 7)
        {
            values.push_back(i);
        }
    }
    auto rng = Random::getRandomEngine();
    shuffle(values.begin(), values.end(), rng);
    int parkIndex = 0;
    int sevenIndex = 0;
    for (int i = 0; i < totalTiles; i++)
    {
        if (resources[i] == ResourceType::Park)
        {
            parkIndex = i;
        }
        if (values[i] == 7)
        {
            sevenIndex = i;
        }
    }
    int temp = values[parkIndex];
    values[parkIndex] = values[sevenIndex];
    values[sevenIndex] = temp;
    return values;
}

int RandomMode::createLayout(Board *board)
{
    vector<std::shared_ptr<Tile>> tiles;
    vector<ResourceType> resources = shuffleResource();
    vector<int> values = shuffleValues(resources);

    int parkIndex;

    for (int i = 0; i < totalTiles; i++)
    {
        if (resources[i] == ResourceType::Park)
            parkIndex = i;

        vector<int> vertices = vector<int>(tileSurroundingVertexIdx[i],
                                           tileSurroundingVertexIdx[i] + tileSurroundingVertexNum);
        tiles.emplace_back(std::make_shared<Tile>(board, vertices, resources[i], values[i]));
    }

    setLayout(board, tiles);

    return parkIndex;
}

