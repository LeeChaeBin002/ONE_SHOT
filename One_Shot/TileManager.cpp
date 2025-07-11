#include "stdafx.h"
#include "TileManager.h"
#include <fstream>
#include <sstream>

bool TileManager::Load(const std::string& imagePath, const std::string& csvPath) {
    if (!texture.loadFromFile(imagePath))
        return false;

    std::ifstream file(csvPath);
    std::string line;
    bool skipHeader = true;

    while (std::getline(file, line)) {
        if (skipHeader) {
            skipHeader = false;
            continue;
        }

        std::stringstream ss(line);
        std::string id, tex, sx, sy, sw, sh, category;

        std::getline(ss, id, ',');
        std::getline(ss, tex, ',');
        std::getline(ss, sx, ',');
        std::getline(ss, sy, ',');
        std::getline(ss, sw, ',');
        std::getline(ss, sh, ',');
        std::getline(ss, category, ',');

        int x = std::stoi(sx);
        int y = std::stoi(sy);
        int w = std::stoi(sw);
        int h = std::stoi(sh);

        tileRects[id] = sf::IntRect(x, y, w, h);
    }

    return true;
}

sf::Sprite TileManager::GetSprite(const std::string& name) {
    sf::Sprite sprite;
    sprite.setTexture(texture);

    if (tileRects.find(name) != tileRects.end()) {
        sprite.setTextureRect(tileRects[name]);
    }

    return sprite;
}
