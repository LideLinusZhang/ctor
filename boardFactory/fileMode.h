#ifndef CTOR_FILEMODE_H
#define CTOR_FILEMODE_H

#include "boardLayoutFactory.h"
#include <iostream>

class FileMode : public BoardLayoutFactory
{
    std::istream& file;
public:
    explicit FileMode(std::istream& file);

    std::shared_ptr<Board> createBoard(View* view) override;
};

#endif //CTOR_FILEMODE_H
