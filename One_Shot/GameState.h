#pragma once
#include <vector>
#include <string>
class GameState
{
public:
	static PlayerState playerState;
	sf::FloatRect rect;
	inline static std::vector<std::string> inventoryItems;

    struct Helper
    {
        static void AddItem(const std::string& itemPath)
        {
            if (std::find(GameState::inventoryItems.begin(), GameState::inventoryItems.end(), itemPath) == GameState::inventoryItems.end())
            {
                GameState::inventoryItems.push_back(itemPath);
            }
        }
    };
};

