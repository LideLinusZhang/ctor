#include <algorithm>
#include "randomGen.h"
#include "board.h"
#include "randomMode.h"
#include "adjacencyTables.h"
#include "tile.h"
#include "dice.h"

using namespace std;

vector<ResourceType> RandomMode::shuffleResource()
{
    vector<ResourceType> resources;
    resources.reserve(totalTiles);

    for(int type = 0; type < totalResourceTypes; type++)
    {
        for (int i = 0; i < tileNumberByResource[type]; i++)
            resources.push_back(static_cast<ResourceType>(type));
    }
    resources.push_back(ResourceType::Park);

    shuffle(resources.begin(), resources.end(), Random::getRandomEngine());
    return resources;
}

vector<int> RandomMode::shuffleValues(std::vector<ResourceType> resources)
{
    vector<int> values;
    for (int i = minRoll; i <= maxRoll; i++)
    {
        values.push_back(i);
        if (i != minRoll && i != maxRoll && i != parkValue)
        {
            values.push_back(i);
        }
    }
    auto rng = Random::getRandomEngine();
    shuffle(values.begin(), values.end(), rng);
    int parkIndex = 0;
    int parkValueIndex = 0;
    for (int i = 0; i < totalTiles; i++)
    {
        if (resources[i] == ResourceType::Park)
        {
            parkIndex = i;
        }
        if (values[i] == parkValue)
        {
            parkValueIndex = i;
        }
    }
    int temp = values[parkIndex];
    values[parkIndex] = values[parkValueIndex];
    values[parkValueIndex] = temp;
    return values;
}

int RandomMode::createLayout(Board *board)
{
    vector<std::unique_ptr<Tile>> tiles;
    vector<ResourceType> resources = shuffleResource();
    vector<int> values = shuffleValues(resources);

    int parkIndex;

    for (int i = 0; i < totalTiles; i++)
    {
        if (resources[i] == ResourceType::Park)
            parkIndex = i;

        vector<int> vertices = vector<int>(tileSurroundingVertexIdx[i],
                                           tileSurroundingVertexIdx[i] + tileSurroundingVertexNum);
        tiles.emplace_back(std::make_unique<Tile>(board, vertices, resources[i], i, values[i]));
    }

    setLayout(board, tiles);

    return parkIndex;
}

