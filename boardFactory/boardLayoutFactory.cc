#include "boardLayoutFactory.h"

void BoardLayoutFactory::setLayout(Board *board, std::vector<std::shared_ptr<Tile>> &tiles)
{
    std::move(tiles.begin(), tiles.end(), std::back_inserter(board->tiles));
    tiles.clear();
}
