#pragma once
#include "Scene.h"
#include "Framework/TextGo.h"
class Title :
    public Scene
{
protected:
    sf::Sound bgm;

    sf::Sprite spritetitle;
    sf::Sprite spriteMode;
    TextGo* screen;
    TextGo* clickStart;
    TextGo* messageText = nullptr;
    int selectedIndex = 0;
    std::vector<std::string> menuOptions = { "Start", "Setting", "Exit" };
public:
    Title();
    ~Title() override = default;

    void ShowMessage(const std::string& msg);
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window);
    void screenchange(const std::string& msg);
    void UpdateMenuText();

};

