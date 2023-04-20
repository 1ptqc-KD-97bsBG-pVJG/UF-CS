#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "Tile.h"

class Board {
    int rows;
    int columns;
    int numMines;
    Tile** tiles;
    int GetMines();
//    MineCounter mineCounter;
public:
    Board(int rows, int columns, int numMines);
    void GenerateTiles(std::string board);
    void Draw(sf::RenderWindow& window, bool displayMines);
    void Clear();
    bool RevealTile(int x, int y);
    void RevealAll();
    void FlagTile(int x, int y);
    bool CheckIfWon();
    ~Board();
};