#include <iostream>
#include "tile.h"

// constructor
Tile::Tile(sf::Texture &texture, sf::Texture &flagTexture) {
    sprite->setTexture(texture);
    sprite2->setTexture(texture);
    flag->setTexture(flagTexture);
}


// accessors
Sprite* Tile::getSprite() {
    return sprite;
}

Sprite* Tile::getSprite2() {
    return sprite2;
}

Sprite* Tile::getFlagSprite() {
    return flag;
}

bool Tile::getIsMine() {
    return isMine;
}

bool Tile::getIsFlagged() {
    return isFlagged;
}

bool Tile::getIsShown() {
    return isShown;
}

int Tile::getAdjMines() {
    return numAdjMines;
}

vector<Tile*>* Tile::getNeighbors() {
    return &neighbors;
}

// mutators
void Tile::setNeighbors(vector<Tile*> &neighborTiles) {
    neighbors = neighborTiles;
    numAdjMines = 0;

    for (int i = 0; i < neighbors.size(); i++) {
        Tile* current = neighbors[i];
        if (current->getIsMine()) {
            numAdjMines++;
        }
    }
}

void Tile::setIsMine(bool isMine) {
    this->isMine = isMine;
}

void Tile::setIsFlagged(bool isFlagged) {
    this->isFlagged = isFlagged;
}

void Tile::setIsShown(bool isShown) {
    this->isShown = isShown;
}

// functions
void Tile::move(float x, float y) {
    sprite->move(x, y);
    sprite2->move(x, y);
    flag->move(x, y);
}

void Tile::placeMine() {
    isMine = true;
}