#include "boardLayoutFactory.h"

int BoardLayoutFactory::getParkIndex(View *view, std::vector<std::shared_ptr<Tile>> tiles) {
    for (auto it : tiles) {
        if (it->getType() == Park) {
            return it->getIndex();
        }
    }
    return 0;
}
