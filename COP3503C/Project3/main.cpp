#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include "board.h"
#include "tile.h"
#include "leaderboard.h"
using namespace std;



int displayWelcome() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    // Load the font
    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        std::cerr << "Error opening font file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Set up welcome text
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    sf::FloatRect welcomeTextBounds = welcomeText.getLocalBounds();
    welcomeText.setOrigin(welcomeTextBounds.left + welcomeTextBounds.width / 2.0f,
                          welcomeTextBounds.top + welcomeTextBounds.height / 2.0f);
    welcomeText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150);

    // Set up input prompt text
    sf::Text inputPromptText("Enter your name:", font, 20);
    inputPromptText.setStyle(sf::Text::Bold);
    inputPromptText.setFillColor(sf::Color::White);
    sf::FloatRect inputPromptTextBounds = inputPromptText.getLocalBounds();
    inputPromptText.setOrigin(inputPromptTextBounds.left + inputPromptTextBounds.width / 2.0f,
                              inputPromptTextBounds.top + inputPromptTextBounds.height / 2.0f);
    inputPromptText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 75);

    // Set up input text
    sf::Text inputText("", font, 18);
    inputText.setStyle(sf::Text::Bold);
    inputText.setFillColor(sf::Color::Yellow);
    sf::FloatRect inputTextBounds = inputText.getLocalBounds();
    inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                        inputTextBounds.top + inputTextBounds.height / 2.0f);
    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);

    // Show "|" as a cursor to indicate the next character position
    sf::Text cursor("|", font, 18);
    cursor.setStyle(sf::Text::Bold);
    cursor.setFillColor(sf::Color::Yellow);
    sf::FloatRect cursorBounds = cursor.getLocalBounds();
    cursor.setOrigin(cursorBounds.left + cursorBounds.width / 2.0f,
                     cursorBounds.top + cursorBounds.height / 2.0f);
    cursor.setPosition(window.getSize().x / 2.0f + inputTextBounds.width / 2.0f + 5, window.getSize().y / 2.0f - 45);
    std::string userName;
    sf::Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (!userName.empty()) {
                        std::cout << userName << std::endl;
                        window.close();
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered) {
                // handle functional button input
                if (event.text.unicode == 8) { // backspace character
                    if (!userName.empty()) {
                        userName.pop_back();
                        inputText.setString(userName);
                        inputTextBounds = inputText.getLocalBounds();
                        inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                                            inputTextBounds.top + inputTextBounds.height / 2.0f);
                        inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
                    }
                }

                    // User entered text
                else if (userName.length() < 10 && isalpha(event.text.unicode)) { // limit to 10 characters
                    userName += static_cast<char>(event.text.unicode);
                    inputText.setString(userName);
                    inputTextBounds = inputText.getLocalBounds();
                    inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                                        inputTextBounds.top + inputTextBounds.height / 2.0f);
                    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
                }
                // Capitalize first character
                if (!userName.empty()) {
                    userName[0] = toupper(userName[0]);
                    inputText.setString(userName);
                    inputTextBounds = inputText.getLocalBounds();
                    inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                                        inputTextBounds.top + inputTextBounds.height / 2.0f);
                    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
                }
                // Convert all other characters to lowercase
                for (int i = 1; i < userName.length(); i++) {
                    userName[i] = tolower(userName[i]);
                    inputText.setString(userName);
                    inputTextBounds = inputText.getLocalBounds();
                    inputText.setOrigin(inputTextBounds.left + inputTextBounds.width / 2.0f,
                                        inputTextBounds.top + inputTextBounds.height / 2.0f);
                    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
                }
            }
        }
        // Refresh cursor position
        cursor.setPosition(window.getSize().x / 2.0f + inputTextBounds.width / 2.0f + 5, window.getSize().y / 2.0f - 45);
        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.draw(inputPromptText);
        window.draw(cursor);
        window.draw(inputText);
        window.display();
    }

    if (userName.empty()) {
        return EXIT_FAILURE;
    }

    window.close();
    return 0;
}

int main()
{
    displayWelcome();
    Board board;
    sf::RenderWindow gameWindow(sf::VideoMode((board.cols * 32), (board.rows * 32 + 100)), "Minesweeper");

    while(gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.onClick(event.mouseButton.x, event.mouseButton.y, "left");
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    board.onClick(event.mouseButton.x, event.mouseButton.y, "right");
                }
            }
        }

        gameWindow.clear();
        board.drawBoard(gameWindow);
        gameWindow.display();
    }
    displayLeaderboard(16 * board.cols, board.rows * 32 - 110);
    return 0;
}