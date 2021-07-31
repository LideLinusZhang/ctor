#ifndef CTOR_GAME_H
#define CTOR_GAME_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>

class View;

class Player;

class Board;

class BoardFactory;

class Dice;

const int totalPlayers = 4;

class Game
{
    // Utilities
    std::shared_ptr<View> view;
    std::shared_ptr<BoardFactory> boardFactory;
    std::istream &input; // Input source.

    // Dices
    std::shared_ptr<Dice> loaded;
    std::shared_ptr<Dice> fair;

    // Game components
    int currentPlayerIndex = -1;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Board> gameBoard;

    void beginTurn(Player* player);
    int roll();
    void obtainResources(int rollResult);
    void moveGeese(Player* player);

    void duringTurn(Player* player);

    void save(const std::string &fileName = "backup.sv");
    void initPlayers(); // Initialize players to their default state.
    void read(const std::string &fileName); // Read the entire class from file.
    explicit Game(std::istream &input); // Only initiate dices.
public:
    explicit Game(const std::string &fileName, std::istream &input = std::cin);
    explicit Game(std::shared_ptr<BoardFactory> factory, std::istream &input = std::cin);

    void play();
};

#endif //CTOR_GAME_H
