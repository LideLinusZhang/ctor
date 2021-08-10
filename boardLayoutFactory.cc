#include "boardLayoutFactory.h"
#include "board.h"
#include "tile.h"

void BoardLayoutFactory::setLayout(Board *board, std::vector<std::unique_ptr<Tile>> &tiles)
{
    std::move(tiles.begin(), tiles.end(), std::back_inserter(board->tiles));
    tiles.clear();
}
