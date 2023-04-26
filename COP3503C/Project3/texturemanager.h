#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

using namespace std;

class TextureManager {
    static unordered_map<string, sf::Texture> textures;
    static void LoadTextures(string name);

public:
    static sf::Texture& getTexture(string name);
    static void Clear();
};