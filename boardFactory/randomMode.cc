#include "../random/random.h"
#include "randomMode.h"

RandomMode::RandomMode(){}

std::vector<ResourceType> RandomMode::shuffleResource() {
    std::vector<ResourceType> resources;
    for (int i = 0; i < 3; i++) {
        resources.push_back(ResourceType::WiFi);
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
    auto rng = Random::getRandomEngine();
    std::shuffle(resources.begin(), resources.end(), rng);
    return resources;
}

std::vector<int> RandomMode::shuffleValues(std::vector<ResourceType> resources) {
    std::vector<int> values;
    for (int i = 2; i < 13; i++) {
        values.push_back(i);
        if (i != 2 && i != 12 && i != 7) {
            values.push_back(i);
        }
    }
    auto rng = Random::getRandomEngine();
    std::shuffle(values.begin(), values.end(), rng);
    int parkIndex = 0;
    int sevenIndex = 0;
    for (int i = 0; i < TOTAL_TILES; i++) {
        if (resources[i] == ResourceType::Park) {
            parkIndex = i;
        }
        if (values[i] == 7) {
            sevenIndex = i;
        }
    }
    int temp = values[parkIndex];
    values[parkIndex] = values[sevenIndex];
    values[sevenIndex] = temp;
    return values;
}

std::vector<std::shared_ptr<Tile>> RandomMode::createLayout(View* view) {
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<ResourceType> resources = shuffleResource();
    std::vector<int> values = shuffleValues(resources);
    
    for (int i = 0; i < TOTAL_TILES; i++) {
        tiles.push_back(std::make_shared<Tile>(tileVertices[i], resources[i], values[i]));
    }
    return tiles;
}

