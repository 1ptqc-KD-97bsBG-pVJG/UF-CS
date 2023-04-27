#include "board.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "leaderboard.h"
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
    else if (!revealedTile.loadFromFile("../files/images/tile_revealed.png"))
        cout << "Error" << endl;

    loadFromFile("../files/board_config.cfg");
    faceSprite.setTexture(faceHappy);
    faceSprite.move(Vector2f(((cols / 2.0) * 32) - 32, 32 * (rows + 0.5f)));
    debugSprite.setTexture(debug);
    debugSprite.move(Vector2f((cols * 32) - 304, 32 * (rows + 0.5f)));
    pauseSprite.setTexture(pause);
    pauseSprite.move(Vector2f((cols * 32) - 240, 32 * (rows + 0.5f)));
    leaderboardSprite.setTexture(leaderboard);
    leaderboardSprite.move(Vector2f((cols * 32) - 176, 32 * (rows + 0.5f)));
    scoreSprite1.move(Vector2f(12, (32 * (rows + 0.5f) + 16)));
    scoreSprite1.setTexture(digits);
    scoreSprite2.move(Vector2f(33, (32 * (rows + 0.5f) + 16)));
    scoreSprite2.setTexture(digits);
    scoreSprite3.move(Vector2f(54, (32 * (rows + 0.5f) + 16)));
    scoreSprite3.setTexture(digits);
    setup();
}


// destructor
Board::~Board() {
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            vector<Tile*> neighbors;
            if (i - 1 >= 0) {
                if (j + 1 >= 0) {
                    if (j + 1 < cols) {
                        Tile* tile = tiles[i - 1][j + 1];
                        neighbors.push_back(tile);
                    }
                    if (j - 1 >= 0) {
                        Tile* tile = tiles[i - 1][j - 1];
                        neighbors.push_back(tile);
                    }
                    Tile* tile = tiles[i - 1][j];
                    neighbors.push_back(tile);
                }

                if (i + 1 < rows) {
                    if (j + 1 < cols) {
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

                if (j + 1 < cols) {
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
                            setSprite(temp->getSprite2(), revealedTile);
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
    window.clear(Color::White);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile* tile = tiles[i][j];
            Sprite* sprite = tile->getSprite();
            Sprite* sprite2 = tile->getSprite2();

            if (isLost) {
                if (tile->getIsShown()) {
                    window.draw(*sprite);
                    window.draw(*sprite2);
                } else {
                    if (tile->getIsMine()) {
                        setSprite(sprite, revealedTile);
                        window.draw(*sprite);
                        window.draw(*sprite2);
                    } else {
                        window.draw(*sprite);
                    }
                }
                if (tile->getIsFlagged() && !tile->getIsShown()) {
                    window.draw(*tile->getFlagSprite());
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
                    if (tile->getIsMine() || tile ->getIsShown()) {
                        window.draw(*sprite2);
                    }
                    if (tile->getIsFlagged() && !tile->getIsShown()) {
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
            if (isPaused) {
                setSprite(sprite, revealedTile);
                window.draw(*sprite);
            } else {
                if (!tile->getIsShown()) {
                    setSprite(tile->getSprite(), hiddenTile);
                }
            }
            if (tile->getIsFlagged() && !tile->getIsShown() && !isPaused) {
                window.draw(*tile->getFlagSprite());
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
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
        int first = hundreds - 48;
        scoreSprite1.setTextureRect(IntRect(first * 21, 0, 21, 32));
    }
    char tens = score[1];
    int second = tens - 48;
    scoreSprite2.setTextureRect(IntRect(second * 21, 0, 21, 32));
    char ones = score[2];
    int third = ones - 48;
    scoreSprite3.setTextureRect(IntRect(third * 21, 0, 21, 32));
}

void Board::addScore(int amount) {
    srand(time(nullptr));
    while (numMines < maxNumMines) {
        int i = rand() % rows;
        int j = rand() % cols;
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
    while (numMines < maxNumMines) {
        int i = rand() % rows;
        int j = rand() % cols;
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
    remainingTiles = rows * cols;
    setSprite(&faceSprite, faceHappy);
    loadFromFile("../files/board_config.cfg");
    numMines = 0;
    generateMines();
    setNeighbors();
}

void Board::loadFromFile(string file) {
    ifstream configFile(file);
    string line;
    getline(configFile, line);
    cols = stoi(line);
    getline(configFile, line);
    rows = stoi(line);
    getline(configFile, line);
    maxNumMines = stoi(line);

    // create the board
    tiles.resize(rows);
    for (int i = 0; i < rows; i++) {
        tiles[i].resize(cols);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!tiles[i][j]) {
                delete tiles[i][j];
            }
            tiles[i][j] = new Tile(hiddenTile, flag);
            tiles[i][j]->move(j * 32, i * 32);
        }
    }
    generateMines();
    setNeighbors();
}

void Board::onClick(int x, int y, string clickType) {

    if (y > (32 * rows + 0.5f) && y < (32 * (rows + 0.5f) + 66)) {
        if ( x >= (((cols / 2.0) * 32) - 32) && x <= ((cols / 2.0) * 32 + 34)) {
            setup();
        }

        if (x >= ((cols * 32) - 304) && x < ((cols * 32) - 238) && !isLost && !isWon) {
            if (isDebug)
                isDebug = false;
            else
                isDebug = true;
        }
        // pause button functionality
        else if (x >= (cols * 32 - 240) && x < (cols * 32 - 174) && !isLost && !isWon) {
            if (isPaused) {
                isPaused = false;
            } else {
                isPaused = true;
            }
        // leaderboard button functionality
        } else if (x >= (cols * 32 - 176) && x < (cols * 32 - 110) && !isLost && !isWon) {

            displayLeaderboard(16 * cols, rows * 32 - 110);
        }
    } else if (!isLost && !isWon && !isPaused) {
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
    cout << tile->getIsShown() << endl;
    setSprite(tile->getSprite(), revealedTile);
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
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Tile* tile = tiles[i][j];
            if (tile->getIsShown()) {
                tile->setIsFlagged(false);
            } else {
                tile->setIsFlagged(true);
            }
        }
    }
    displayLeaderboard(16 * cols, rows * 32 - 110);
}