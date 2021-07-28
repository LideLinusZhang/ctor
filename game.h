#ifndef CTOR_GAME_H
#define CTOR_GAME_H

#include <vector>
#include <memory>

class View;
class Player;
class Board;
class BoardFactory;
class FileMode;

class Game
{
    std::shared_ptr<View> view;
    std::shared_ptr<Board> gameBoard;
    Dice loaded;
    Dice fair;
    BoardFactory& boardFactory;
    std::vector<std::shared_ptr<Player>> players;

    void save();
    void init();
    void init(std::string fileName);
public:
    explicit Game(std::string fileName);
    explicit Game(BoardFactory& factory);
    Game(FileMode& factory, std::string fileName);

    void play();
};

#endif //CTOR_GAME_H
