#include "board.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace sf;

Board::Board() {

    if (!digits.loadFromFile("../files/images/digits.png"))
        cout << "Error" << endl;
    else if (!debug.loadFromFile("../files/images/debug.png"))
        cout << "Error" << endl;
    else if (!faceHappy.loadFromFile("../files/images/face_happy.png"))
        cout << "Error" << endl;
    else if (!faceLose.loadFromFile("../files/images/face_lose.png"))
        cout << "Error" << endl;
    else if (!faceWin.loadFromFile("../files/images/face_win.png"))
        cout << "Error" << endl;
    else if (!flag.loadFromFile("../files/images/flag.png"))
        cout << "Error" << endl;
    else if (!mine.loadFromFile("../files/images/mine.png"))
        cout << "Error" << endl;
    else if (!number1.loadFromFile("../files/images/number_1.png"))
        cout << "Error" << endl;
    else if (!number2.loadFromFile("../files/images/number_2.png"))
        cout << "Error" << endl;
    else if (!number3.loadFromFile("../files/images/number_3.png"))
        cout << "Error" << endl;
    else if (!number4.loadFromFile("../files/images/number_4.png"))
        cout << "Error" << endl;
    else if (!number5.loadFromFile("../files/images/number_5.png"))
        cout << "Error" << endl;
    else if (!number6.loadFromFile("../files/images/number_6.png"))
        cout << "Error" << endl;
    else if (!number7.loadFromFile("../files/images/number_7.png"))
        cout << "Error" << endl;
    else if (!number8.loadFromFile("../files/images/number_8.png"))
        cout << "Error" << endl;
    else if (!pause.loadFromFile("../files/images/pause.png"))
        cout << "Error" << endl;
    else if (!leaderboard.loadFromFile("../files/images/leaderboard.png"))
        cout << "Error" << endl;
    else if (!hiddenTile.loadFromFile("../files/images/tile_hidden.png"))
        cout << "Error" << endl;
    else if (!shownTile.loadFromFile("../files/images/tile_revealed.png"))
        cout << "Error" << endl;




    faceSprite.setTexture(faceHappy);
    faceSprite.move(Vector2f(6 * 64, 32 * 16));
    debugSprite.setTexture(debug);
    debugSprite.move(Vector2f(8 * 64, 32 * 16));
    pauseSprite.setTexture(pause);
    pauseSprite.move(Vector2f(9 * 64, 32 * 16));
    leaderboardSprite.setTexture(leaderboard);
    leaderboardSprite.move(Vector2f(10 * 64, 32 * 16));
    scoreSprite1.move(Vector2f(0, 32 * 16));
    scoreSprite1.setTexture(digits);
    scoreSprite2.move(Vector2f(21, 32 * 16));
    scoreSprite2.setTexture(digits);
    scoreSprite3.move(Vector2f(42, 32 * 16));
    scoreSprite3.setTexture(digits);
    setup();
}






// destructor
Board::~Board() {
    // FIXME: correct this hardcoding
    for (int i =9; i < 16; i++) {
        for(int j = 0; j < 25; j++) {
            delete tiles[i][j];
        }
    }
}


// accessors
Tile* Board::getTile(int row, int column) {
    return tiles[row][column];
}

// mutators
void Board::setNeighbors() {
    // FIXME: correct this hardcoding
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            vector<Tile*> neighbors;
            if (i - 1 >= 0) {
                if (j + 1 >= 0) {
                    if (j + 1 < 25) {
                        Tile* tile = tiles[i - 1][j + 1];
                        neighbors.push_back(tile);
                    }
                    if (j - 1 >= 0) {
                        Tile* tile = tiles[i - 1][j + 1];
                        neighbors.push_back(tile);
                    }
                    Tile* tile = tiles[i - 1][j];
                    neighbors.push_back(tile);
                }

                if (i + 1 < 16) {
                    if (j + 1 < 25) {
                        Tile* tile = tiles[i + 1][j + 1];
                        neighbors.push_back(tile);
                    }
                    if (j - 1 >= 0) {
                        Tile* tile = tiles[i + 1][j - 1];
                        neighbors.push_back(tile);
                    }
                    Tile* tile = tiles[i + 1][j];
                    neighbors.push_back(tile);
                }

                if (j + 1 < 25) {
                    Tile* tile = tiles[i][j + 1];
                    neighbors.push_back(tile);
                }
                if (j - 1 >= 0) {
                    Tile* tile = tiles[i][j - 1];
                    neighbors.push_back(tile);
                }
                Tile* temp = tiles[i][j];
                temp->setNeighbors(neighbors);
                if (temp->getIsMine()) {
                    setSprite(temp->getSprite2(), mine);
                } else {
                    int numAdjacentMines = temp->getAdjMines();
                    switch (numAdjacentMines) {
                        case 0:
                            setSprite(temp->getSprite2(), shownTile);
                            break;
                        case 1:
                            setSprite(temp->getSprite2(), number1);
                            break;
                        case 2:
                            setSprite(temp->getSprite2(), number2);
                            break;
                        case 3:
                            setSprite(temp->getSprite2(), number3);
                            break;
                        case 4:
                            setSprite(temp->getSprite2(), number4);
                            break;
                        case 5:
                            setSprite(temp->getSprite2(), number5);
                            break;
                        case 6:
                            setSprite(temp->getSprite2(), number6);
                            break;
                        case 7:
                            setSprite(temp->getSprite2(), number7);
                            break;
                        case 8:
                            setSprite(temp->getSprite2(), number8);
                            break;
                    }
                }
            }
        }
    }
}

void Board::setSprite(sf::Sprite* sprite, sf::Texture &texture) {
    sprite->setTexture(texture);
}


void Board::drawBoard(RenderWindow &window) {
    // FIXME: correct this hardcoding
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile* tile = tiles[i][j];
            Sprite* sprite = tile->getSprite();
            Sprite* sprite2 = tile->getSprite2();

            if (isLost) {
                if (tile->getIsShown()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                } else {
                    if (tile->getIsMine()) {
                        setSprite(sprite, shownTile);
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    } else {
                        window.draw(*sprite);
                    }
                }
            } else if (isWon) {
                if (tile->getIsShown()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                } else {
                    if (tile->getIsMine()) {
                        window.draw(*sprite);
                        window.draw(*tile->getFlagSprite());
                    }
                }
            } else {
                if (isDebug) {
                    window.draw(*sprite);
                    if (tile->getIsMine() || tile->getIsShown()) {
                        window.draw(*tile->getFlagSprite());
                    }
                } else {
                    if (tile->getIsShown()) {
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    }
                    else {
                        window.draw(*sprite);
                        if (tile->getIsShown()) {
                            window.draw(*tile->getFlagSprite());
                        }
                    }
                }
            }
        }
    }
    updateScore();
    window.draw(faceSprite);
    window.draw(debugSprite);
    window.draw(pauseSprite);
    window.draw(leaderboardSprite);
    window.draw(scoreSprite1);
    window.draw(scoreSprite2);
    window.draw(scoreSprite3);
}

void Board::updateScore() {
    int flagged = 0;
    // FIXME: correct this hardcoding
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile* tile = tiles[i][j];
            if (tile->getIsFlagged()) {
                flagged++;
            }
        }
    }
    int currentScore = numMines - flagged;
    score = to_string(currentScore); + "";
    char hundreds = score[0];
    if (hundreds == '-') {
        scoreSprite1.setTextureRect(IntRect(210, 0, 21, 32));
    }
    else {
        // FIXME: correct this hardcoding
        int first = hundreds - 48;
        scoreSprite1.setTextureRect(IntRect(first * 21, 0, 21, 32));
    }
    char tens = score[1];
    // FIXME: correct this hardcoding
    int second = tens - 48;
    scoreSprite2.setTextureRect(IntRect(second * 21, 0, 21, 32));
    char ones = score[2];
    int third = ones - 48;
    scoreSprite3.setTextureRect(IntRect(third * 21, 0, 21, 32));
}


void Board::addScore(int amount) {
    srand(time(nullptr));
    while (numMines < 50) {
        // FIXME: correct this hardcoding
        int i = rand() % 16;
        int j = rand() % 25;
        Tile* tile = tiles[i][j];
        if (!tile->getIsMine()) {
            tile->placeMine();
            setSprite(tile->getSprite2(), mine);
            numMines++;
            remainingTiles--;
        }
    }
}

void Board::generateMines() {
    srand(time(nullptr));
    while (numMines < 50) {
        // FIXME: correct this hardcoding
        int i = rand() % 16;
        int j = rand() % 25;
        Tile* tile = tiles[i][j];
        if (!tile->getIsMine()) {
            tile->placeMine();
            setSprite(tile->getSprite2(), mine);
            numMines++;
            remainingTiles--;
        }
    }
}


void Board::setup() {
    isLost = false;
    isWon = false;
    // FIXME: correct this hardcoding
    remainingTiles = 400;
    setSprite(&faceSprite, faceHappy);
    // FIXME: correct this hardcoding
    for ( int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if (!tiles[i][j]) {
                delete tiles[i][j];
            }
            tiles[i][j] = new Tile(hiddenTile, flag);
            // FIXME: correct this hardcoding
            tiles[i][j]->move(j * 32, i * 32);
        }
    }
    numMines = 0;
    generateMines();
    setNeighbors();
}

void Board::loadFromFile(string file) {
    char x;
    fstream File(file, fstream::in);
    int i = 0;
    int j = 0;
    numMines = 0;
    remainingTiles = 400;

    while (File >> x) {
        Tile* tile = tiles[i][j];
        setSprite(tile->getSprite(), hiddenTile);
        if (x == '0') {
            tile->setIsMine(false);
            tile->setIsShown(false);
            setSprite(tile->getSprite2(), shownTile);
        }
        else if (x == '1') {
            tile->setIsMine(true);
            remainingTiles--;
            tile->setIsShown(false);
            numMines++;
            setSprite(tile->getSprite2(), mine);
        }
        j++;
        if (j > 24) {
            j = 0;
            i++;
        }
    }
    setNeighbors();
}

void Board::onClick(int x, int y, string clickType) {
    // FIXME: correct this hardcoding
    if (y > 512 && y < 578) {
        if (x >= (64 * 8) && x <= (64 * 9) && !isLost && !isWon) {
            if (isDebug)
                isDebug = false;
            else
                isDebug = true;
        }
    } else if (!isLost && !isWon) {
        int row = y / 32;
        int column = x / 32;
        Tile* temp = tiles[row][column];
        if (clickType == "left") {
            if (!temp->getIsFlagged() && !temp->getIsShown()) {
                onReveal(temp);
            }
        } else if (clickType == "right") {
            toggleFlag(temp);
        }
    }
}

void Board::onReveal(Tile* tile) {
    tile->setIsShown(true);
    setSprite(tile->getSprite(), shownTile);
    if (tile->getIsMine()) {
        endGame();
    } else {
        remainingTiles--;
        if (remainingTiles <= 0) {
            winGame();
        }
        if (tile->getAdjMines() == 0) {
            vector<Tile*>* neighbors = tile->getNeighbors();
            int size = neighbors->size();
            for (int i = 0; i < size; i++) {
                Tile* temp = neighbors->at(i);
                if (!temp->getIsShown()) {
                    onReveal(temp);
                }
            }
        }
    }
}


void Board::toggleFlag(Tile* tile) {
    if (tile->getIsFlagged()) {
        tile->setIsFlagged(false);
    } else {
        tile->setIsFlagged(true);
    }
}

void Board::endGame() {
    isDebug = false;
    isLost = true;
    setSprite(&faceSprite, faceLose);
}


void Board::winGame() {
    isDebug = false;
    isWon = true;
    setSprite(&faceSprite, faceWin);
    // FIXME: correct this hardcoding
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            Tile* tile = tiles[i][j];
            if (tile->getIsShown()) {
                tile->setIsFlagged(false);
            } else {
                tile->setIsFlagged(true);
            }
        }
    }
}