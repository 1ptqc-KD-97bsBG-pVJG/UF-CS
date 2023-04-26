#include "texturemanager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTextures(string name) {
    string path = "images/" + name + ".png";
    textures[name].loadFromFile(path);
}

sf::Texture& TextureManager::getTexture(string name) {
    if (textures.find(name) == textures.end()) {
        LoadTextures(name);
    }
    return textures[name];
}

void TextureManager::Clear() {
    textures.clear();
}