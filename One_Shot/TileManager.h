#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TileManager {
private:
    sf::Texture texture;
    std::unordered_map<std::string, sf::IntRect> tileRects;

public:
    bool Load(const std::string& imagePath, const std::string& csvPath);
    sf::Sprite GetSprite(const std::string& name);
};
