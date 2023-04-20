#pragma once
#include <SFML/Graphics.hpp>

class Tile {
    sf::Sprite sprite;
    sf::Texture texture;
    bool isFlagged;
    bool isRevealed;
    int numAdjacentMines;
    Tile* adjacentTiles[8] = {nullptr};

public:
    bool isMine;
    Tile();
    bool CheckIfRevealed();
    void SetAdjacentTiles(Tile* adjacentTiles[8]);
    void SetPosition(int x, int y);
    void Draw(sf::RenderWindow& window, bool displayMines);
    void Reveal();
    void Flag();

};