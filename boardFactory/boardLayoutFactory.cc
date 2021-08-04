#include "boardLayoutFactory.h"

void BoardLayoutFactory::setLayout(Board *board, std::vector<std::shared_ptr<Tile>> &tiles)
{
     std::copy(tiles.begin(), tiles.end(), std::back_inserter(board->tiles));
}
