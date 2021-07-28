#ifndef CTOR_FILEMODE_H
#define CTOR_FILEMODE_H

#include "boardFactory.h"
#include <iostream>

class FileMode : public BoardFactory
{
    std::istream& file;
public:
    explicit FileMode(std::istream& file);

    std::shared_ptr<Board> createBoard() override;
};

#endif //CTOR_FILEMODE_H
