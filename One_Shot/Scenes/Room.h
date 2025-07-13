#pragma once
#include "Scene.h"
#include "TileManager.h"
class Room :
    public Scene
{
protected:
    sf::Sprite spritetitle;
    sf::Sprite spriteMode;
    TileManager tileManager;
    sf::Sprite background;
   // sf::Sprite playerSprite
   //Animator animator;
    TextGo* screen;
    TextGo* clickStart;
    SceneIds changeScene = SceneIds::Setting;
public:
    Room();
    ~Room() override = default;

    void screenchange(const std::string& msg);
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window);
};

