#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Tile {
    Sprite* sprite = new Sprite;
    Sprite* sprite2 = new Sprite;
    Sprite* flag = new Sprite;

    bool isShown = false;
    bool isMine = false;
    bool isFlagged = false;
    int numAdjMines = 0;
    vector<Tile*> neighbors;

public:

    Tile(Texture& texture, Texture& flagTexture);

    // accessors
    Sprite* getSprite();
    Sprite* getSprite2();
    Sprite* getFlagSprite();

    bool getIsMine();
    bool getIsFlagged();
    bool getIsShown();
    int getAdjMines();
    vector<Tile*>* getNeighbors();

    // mutators
    void setNeighbors(vector<Tile*> &neighborTiles);
    void setIsMine(bool isMine);
    void setIsFlagged(bool isFlagged);
    void setIsShown(bool isShown);

    // functions
    void move(float x, float y);
    void placeMine();
};