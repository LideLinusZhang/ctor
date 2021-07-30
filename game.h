#ifndef CTOR_GAME_H
#define CTOR_GAME_H

#include <vector>
#include <memory>
#include <string>

#define TOTAL_PLAYERS 4

class View;
class Player;
class Board;
class BoardFactory;
class Dice;

class Game
{
    std::shared_ptr<View> view;
    std::shared_ptr<Board> gameBoard;
    std::unique_ptr<Dice> loaded;
    std::unique_ptr<Dice> fair;
    std::shared_ptr<BoardFactory> boardFactory;
    std::vector<std::shared_ptr<Player>> players;

    void save();
    void initPlayers(); // Initialize players to their default state.
    void read(std::string& fileName); // Read the entire class from file.
    Game(); // Only initiate dices.
public:
    explicit Game(std::string& fileName);
    explicit Game(std::shared_ptr<BoardFactory> factory);

    void play();
};

#endif //CTOR_GAME_H
