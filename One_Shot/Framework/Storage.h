#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "SpriteGo.h"

class Storage :
    public Scene
{
protected:
    std::vector<std::string> items;
    int selectedIndex = 0;
    TextGo* selectedText = nullptr;
    sf::Sprite inventoryBg;
    std::vector<sf::Sprite> slotSprites;
    std::vector<sf::Sprite> itemIcons;

public:
    Storage();
    ~Storage()override = default;
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window)override;
    void Release() override;
    void screenchange(const std::string& msg);
    void Exit()override;
    void UpdateSelectionText();
};

