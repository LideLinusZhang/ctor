#include "fileMode.h"

FileMode::FileMode(std::istream& file) : file{file} {
}
std::shared_ptr<Board> FileMode::createBoard(View* view) {
    std::vector<std::shared_ptr<Vertex>> vertices = createVertices(view);
    std::vector<std::shared_ptr<Edge>> edges = createEdges(view, &vertices);
    std::vector<std::vector<int>> vertexTiles = createTileVertices();
    std::vector<std::shared_ptr<Tile>> tiles;
    int resource = 0;
    int value = 0;
    ResourceType type;
    for (int i = 0; i < TOTAL_TILES; i++) {
        file >> resource;
        file >> value;
        ResourceType type;
        switch (resource) {
            case 0:
                type = ResourceType::Brick;
            case 1:
                type = ResourceType::Energy;
            case 2:
                type = ResourceType::Glass;
            case 3:
                type = ResourceType::Heat;
            case 4:
                type = ResourceType::Wifi;
            case 5:
                type = ResourceType::Park;
        }
        tiles.push_back(std::make_shared<Tile>(this, vertexTiles[i], type, value));
    }
    int geesePosition = boardFactory::geeseParkIndex(view, tiles);
    return make_shared<Board>(view, tiles, edges, vertices, geesePosition);
}
