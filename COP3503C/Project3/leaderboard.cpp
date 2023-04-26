#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include "leaderboard.h"
using namespace std;

int displayLeaderboard() {
    //    open leaderboard file to load times and names in the format: 07:41,Alex
    sf::Event event;

    ifstream leaderboardFile("../files/leaderboard.txt");
    if (!leaderboardFile) {
        cerr << "Error opening leaderboard file!" << endl;
        return EXIT_FAILURE;
    }
    string line;
    vector<string> leaderboard;
    int lineIterator = 1;
    while (getline(leaderboardFile, line)) {
        string formattedLine;
        int postition = line.find(",");
        formattedLine = to_string(lineIterator) + ".\t" + line.substr(0, postition) + "\t" + line.substr(postition + 1, line.length());
        leaderboard.push_back(formattedLine);
        lineIterator++;
    }
    leaderboardFile.close();

    sf::RenderWindow leaderboardWindow(sf::VideoMode(800, 600), "Minesweeper");
    // Load the font
    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        std::cerr << "Error opening font file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Set up leaderboard text
    // FIXME: fix sizing and positioning
    sf::Text leaderboardTitle("LEADERBOARD", font, 20);
    leaderboardTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardTitle.setFillColor(sf::Color::White);
    sf::FloatRect leaderboardTitleBounds = leaderboardTitle.getLocalBounds();
    leaderboardTitle.setOrigin(leaderboardTitleBounds.left + leaderboardTitleBounds.width / 2.0f,
                               leaderboardTitleBounds.top + leaderboardTitleBounds.height / 2.0f);
    leaderboardTitle.setPosition(leaderboardWindow.getSize().x / 2.0f, leaderboardWindow.getSize().y / 2.0f - 120);

    leaderboardWindow.clear(sf::Color::Blue);
    leaderboardWindow.draw(leaderboardTitle);

    for (int i = 0; i < leaderboard.size(); i++) {
        // display leaderboard text on screen
        // FIXEME: fix sizing and positioning
        // FIXME: needs to be centered too
        sf::Text leaderboardText(leaderboard[i], font, 18);
        leaderboardText.setFillColor(sf::Color::White);
        sf::FloatRect leaderboardTextBounds = leaderboardText.getLocalBounds();
        leaderboardText.setOrigin(leaderboardTextBounds.left + leaderboardTextBounds.width / 2.0f,
                                  leaderboardTextBounds.top + leaderboardTextBounds.height / 2.0f);
        leaderboardText.setPosition(leaderboardWindow.getSize().x / 2.0f, leaderboardWindow.getSize().y / 2.0f - 100 + (i * 50)); // FIXME: not sure how much spacing is required between scores
        //    leaderboardTitle.setPosition(x: ((board.num_cols*16) / 2.0f, y: (((board.num_rows*16)+50) / 2.0f)+20);
        leaderboardWindow.draw(leaderboardText);
    }


    leaderboardWindow.display();

    while (leaderboardWindow.isOpen()) {
        // Gameplay code here
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
    }




    return 0;
}
