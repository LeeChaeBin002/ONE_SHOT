#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <unordered_set>

class TileManager {
private:
    sf::Texture texture;
    std::unordered_map<std::string, sf::IntRect> tileRects;
    std::unordered_set<std::string> collidableTiles;

public:
    bool Load(const std::string& imagePath, const std::string& csvPath);
    sf::Sprite GetSprite(const std::string& name);
    bool IsCollidable(const std::string& name) const;
};
