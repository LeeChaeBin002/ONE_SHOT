#pragma once

class Tile
{
public:
    sf::Sprite sprite;

    Tile() = default;
    Tile(const sf::Texture& texture, const sf::IntRect& rect, const sf::Vector2f& pos)
    {
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
        sprite.setPosition(pos);
    }
};

class TileManager
{
private:
	sf::Texture texture;
	std::vector<Tile> tiles;
	
public:
	bool LoadTileset(const std::string& textureFile, const std::string& csvFile);
	void Draw(sf::RenderWindow& window);
};

