#include <SFML/Graphics.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
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

//        You will also display the contents of the "leaderboard.txt" file with the following specifications:
//        – Style: Bold
//        – Color: White (Default)
//        – Size: 18px
//        – Position: width/2.0f, height/2.0f + 20
//        – Note: It will be easier for you if you store all the rows in a string separated by two line spaces (\n\n). Then you can use this string to create a sf::Text and set its position as specified above. Also, you can give a tab space (\t) between the values
//        i.e., ("1." + "\t" + "07:01" + "\t" + "Alex").



        leaderboard.push_back(formattedLine);
        lineIterator++;
    }
    leaderboardFile.close();



    std::cout << "Iterated through leaderboard file" << std::endl;





    sf::RenderWindow leaderboardWindow(sf::VideoMode(800, 600), "Minesweeper");
    // Load the font
    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        std::cerr << "Error opening font file!" << std::endl;
        return EXIT_FAILURE;
    }

    // Set up leaderboard text
    sf::Text leaderboardTitle("LEADERBOARD", font, 20);
    leaderboardTitle.setStyle(sf::Text::Bold | sf::Text::Underlined);
    leaderboardTitle.setFillColor(sf::Color::White);
    sf::FloatRect leaderboardTitleBounds = leaderboardTitle.getLocalBounds();
    leaderboardTitle.setOrigin(leaderboardTitleBounds.left + leaderboardTitleBounds.width / 2.0f,
                               leaderboardTitleBounds.top + leaderboardTitleBounds.height / 2.0f);
    leaderboardTitle.setPosition(leaderboardWindow.getSize().x / 2.0f, leaderboardWindow.getSize().y / 2.0f - 200);

    leaderboardWindow.clear(sf::Color::Blue);
    leaderboardWindow.draw(leaderboardTitle);

    std::cout << "iterating..." << std::endl;
    for (int i = 0; i < leaderboard.size(); i++) {
        // display leaderboard text on screen
        std::cout << leaderboard[i] << std::endl;
        sf::Text leaderboardText(leaderboard[i], font, 18);
        leaderboardText.setFillColor(sf::Color::White);
        sf::FloatRect leaderboardTextBounds = leaderboardText.getLocalBounds();
        leaderboardText.setOrigin(leaderboardTextBounds.left + leaderboardTextBounds.width / 2.0f,
                              leaderboardTextBounds.top + leaderboardTextBounds.height / 2.0f);
        leaderboardText.setPosition(leaderboardWindow.getSize().x / 2.0f, leaderboardWindow.getSize().y / 2.0f - 100 + (i * 50)); // FIXME: not sure how much spacing is required between scores
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

int main()
{
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
                    std::cout << "enter key pressed" << std::endl;
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
    window.close();

    // Launch game window, but only if the player has entered a name
    if (userName.empty()) {
        return EXIT_FAILURE;
    }
    else {
        std::cout << "Calling function" << std::endl;
        displayLeaderboard();

    }
}