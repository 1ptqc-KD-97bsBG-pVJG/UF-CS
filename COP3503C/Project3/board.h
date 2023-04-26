#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "tile.h"

//TODO: finish this file

class Board {
    int numMines;
    Tile* tiles[16][25];
    int GetMines();
    bool isDebug = false;
    bool isLost = false;
    bool isWon = false;
    int remainingTiles = 400;

    Texture digits, debug, faceHappy, faceLose, faceWin, flag, mine, number1, number2, number3, number4, number5,
            number6, number7, number8, pause, play, leaderboard, hiddenTile, shownTile;

    Sprite faceSprite, debugSprite, pauseSprite, playSprite, leaderboardSprite, scoreSprite1, scoreSprite2, scoreSprite3;

    string score = "000";

public:
    // Constructor
    Board();

    // Destructor
    ~Board();

    // Accessors
    Tile* getTile(int row, int column);

    // Mutators
    void setNeighbors();

    void setSprite(Sprite* sprite, Texture &text);

    // Functions
    void drawBoard(RenderWindow &window);

    void updateScore();

    void addScore(int toAdd);

    void generateMines();

    void setup();

    void loadFromFile(string fileName);

    void onClick(int x, int y, string clickType);

    void onReveal(Tile* tile);

    void toggleFlag(Tile* tile);

    void endGame();
    void winGame();
};