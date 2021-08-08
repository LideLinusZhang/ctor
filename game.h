#ifndef CTOR_GAME_H
#define CTOR_GAME_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "controller.h"

class View;

class Player;

class Board;

class BoardLayoutFactory;

class Dice;

const int totalPlayers = 4;

class Game : public Controller
{
    // Utilities
    std::shared_ptr<View> view;
    std::shared_ptr<BoardLayoutFactory> boardFactory;

    // Dices
    std::shared_ptr<Dice> loaded;
    std::shared_ptr<Dice> fair;

    // Game components
    static const int gameBeginningPlayerIndex = -1; // The index before building initial buildings.
    int currentPlayerIndex = gameBeginningPlayerIndex;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Board> gameBoard;

    void buildInitial(Player *player);

    void beginTurn(Player *player);
    int roll();
    int moveGeese(); // Returns the new position of the geese.
    void stealFromOthers(Player *player, int geesePosition);
    void obtainResources(int rollResult);

    void duringTurn(Player *player);
    void tradeWithOthers(Player *player);

    bool endGame(); // true: play again, false: just exit.

    void save(const std::string &fileName = "backup.sv");
    void initPlayers(); // Add players in their default state to the empty player vector.
    void read(const std::string &fileName); // Read the entire class from file.

    explicit Game(std::istream &input); // Only initiate dices.
public:
    explicit Game(const std::string &fileName, std::istream &input = std::cin);
    explicit Game(std::shared_ptr<BoardLayoutFactory> factory, std::istream &input = std::cin);

    bool play(); // true: play again, false: just exit.
    ~Game() = default;
};

#endif //CTOR_GAME_H
