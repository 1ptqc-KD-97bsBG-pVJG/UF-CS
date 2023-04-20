#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

using namespace std;

class TextureManager {
    unordered_map<string, sf::Texture> textures;
    void LoadTextures(string name);

public:
    sf::Texture& getTextures(string name);
    void Clear();
};