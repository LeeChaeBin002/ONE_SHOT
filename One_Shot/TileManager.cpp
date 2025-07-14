#include "stdafx.h"
#include "TileManager.h"
#include <iostream>
bool TileManager::LoadTileset(const std::string& textureFile, const std::string& csvFile)
{
    if (!texture.loadFromFile(textureFile))
    {
        std::cerr << "Failed to load texture file: " << textureFile << std::endl;
        return false;
    }
    tiles.clear();
    // �� Ÿ�� �ϳ��� �߰�
    Tile darkWall;
    darkWall.sprite.setTexture(texture);
    darkWall.sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
    darkWall.sprite.setPosition(100, 100);
    tiles.push_back(darkWall);


    return true;
}

void TileManager::Draw(sf::RenderWindow& window)
{
    for (auto& tile : tiles)
    {
        window.draw(tile.sprite);
    }
}
