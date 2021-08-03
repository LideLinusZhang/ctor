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
    int currentPlayerIndex = -1;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Board> gameBoard;

    void beginTurn(Player *player);
    int roll();
    int moveGeese(Player *player); // Returns the new position of the geese.
    void stealFromOthers(Player *player, int geesePosition);
    void obtainResources(int rollResult);

    void duringTurn(Player *player);
    void tradeWithOthers(Player *player);

    bool endGame(); // true: play again, false: just exit.

    void save(const std::string &fileName = "backup.sv");
    void initPlayers(); // Initialize players to their default state.
    void read(const std::string &fileName); // Read the entire class from file.
    explicit Game(std::istream &input); // Only initiate dices.
public:
    explicit Game(const std::string &fileName, std::istream &input = std::cin);
    explicit Game(std::shared_ptr<BoardLayoutFactory> factory, std::istream &input = std::cin);

    bool play(); // true: play again, false: just exit.
};

#endif //CTOR_GAME_H
