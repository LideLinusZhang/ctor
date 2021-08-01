#include "board.h"

Board::Board(View* view, std::vector<std::shared_ptr<Tile>> tiles, 
            std::vector<std::shared_ptr<Edge>> edges,
            std::vector<std::shared_ptr<Vertex>> vertices, 
            int geeseInitialPosition)
            : view{view}, tiles{tiles}, edges{edges}, vertices{vertices}, geese{geeseInitialPosition} {
}
            
Tile* Board::getTile(int index) const {
    return tiles[index].get();
}

Edge* Board::getEdge(int index) const {
    return edges[index].get();
}

Vertex* Board::getVertex(int index) const {
    return vertices[index].get();
}

bool Board::tryMoveGeese(int tileIndex) {
    return geese.tryMoveTo(tileIndex);
}

void Board::print() const {
}
