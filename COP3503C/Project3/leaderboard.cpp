#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "leaderboard.h"
using namespace std;

int displayLeaderboard(int windowWidth, int windowHeight) {
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
        int position = line.find(",");
        formattedLine = to_string(lineIterator) + ".\t" + line.substr(0, position) + "\t" + line.substr(position + 1, line.length());
        leaderboard.push_back(formattedLine);
        lineIterator++;
    }
    leaderboardFile.close();

    float columnSpacing = windowWidth / 5.0f;

    sf::RenderWindow leaderboardWindow(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");
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
    leaderboardTitle.setPosition(leaderboardWindow.getSize().x / 2.0f, leaderboardWindow.getSize().y / 2.0f - 150);

    leaderboardWindow.clear(sf::Color::Blue);
    leaderboardWindow.draw(leaderboardTitle);

    for (int i = 0; i < leaderboard.size(); i++) {
        stringstream ss(leaderboard[i]);
        string position, time, name;
        getline(ss, position, '\t');
        getline(ss, time, '\t');
        getline(ss, name);

        sf::Text positionText(position, font, 18);
        positionText.setFillColor(sf::Color::White);
        positionText.setPosition(columnSpacing * 1.2, leaderboardWindow.getSize().y / 2.0f - 80 + (i * 60));

        sf::Text timeText(time, font, 18);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(columnSpacing * 2, leaderboardWindow.getSize().y / 2.0f - 80 + (i * 60));

        sf::Text nameText(name, font, 18);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(columnSpacing * 3.2, leaderboardWindow.getSize().y / 2.0f - 80 + (i * 60));

        leaderboardWindow.draw(positionText);
        leaderboardWindow.draw(timeText);
        leaderboardWindow.draw(nameText);
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
