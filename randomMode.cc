#include "randomMode.h"

RandomMode::RandomMode(const int seed) : seed{seed} {}

std::vector<ResourceType> RandomMode::shuffleResource() {
    std::vector<ResourceType> resources;
    for (int i = 0; i < 3; i++) {
        resources.push_back(ResourceType::Wifi);
    }
    for (int i = 0; i < 3; i++) {
        resources.push_back(ResourceType::Heat);
    }
    for (int i = 0; i < 3; i++) {
        resources.push_back(ResourceType::Brick);
    }
    for (int i = 0; i < 3; i++) {
        resources.push_back(ResourceType::Glass);
    }
    for (int i = 0; i < 3; i++) {
        resources.push_back(ResourceType::Energy);
    }
    resources.push_back(ResourceType::Park);
    auto rng = std::default_random_engine{seed};
    std::shuffle(resources.begin(), resources.end(), rng);
    return resources;
}

std::vector<int> RandomMode::shuffleValues(std::vector<ResourceType> resources) {
    std::vector<int> values;
    for (int i = 2; i < 13; i++) {
        values.push_back(i);
        if (i != 2 || i != 12 || i != 7) {
            values.push_back(i);
        }
    }
    auto rng = std::default_random_engine {seed};
    std::shuffle(values.begin(), values.end(), rng);
    int parkIndex = 0;
    int sevenIndex = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        if (resources[i] == ResourceType::Park) {
            parkIndex = i;
        }
        if (values[i] = 7) {
            sevenIndex = i;
        }
    }
    int temp = values[parkIndex];
    values[parkIndex] = values[sevenIndex];
    values[sevenIndex] = temp;
    return values;
}

std::shared_ptr<Board> randomMode::createBoard(View* view) {
    std::vector<std::shared_ptr<Vertex>> vertices = BoardFactory::createVertices(view);
    std::vector<std::shared_ptr<Edge>> edges = BoardFactory::createEdges(view, &vertices);
    std::vector<std::vector<int>> vertexTiles = BoardFactory::createTileVertices();
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<ResourceType> resources = shuffleResource();
    std::vector<int> values = shuffleValues(resources);
    
    for (int i = 0; i < TOTAL_TILES; i++) {
        tiles.push_back(std::make_shared<Tile>(this, vertices[i], resources[i], values[i]));
    }
    int geesePosition = BoardFactory::getParkIndex(view, tiles);
    return std::make_shared<Board>(view, tiles, edges, vertices, geesePosition);
}
