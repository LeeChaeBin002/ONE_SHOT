#pragma once
#include "Scene.h"
#include "TileManager.h"
#include "Room.h"
#include "player.h"
class Room :
    public Scene
{
protected:
    TileManager tileMgr;
    AniPlayer* player = nullptr;
    sf::Sprite wall;
    sf::Sprite bed;
    sf::Sprite spritetitle;
    sf::Sprite spriteMode;
    TileManager tileManager;
    sf::Sprite background;
    bool positionSet = false;
   // sf::Sprite playerSprite
   //Animator animator;
    TextGo* screen;
    TextGo* clickStart;
    SceneIds changeScene = SceneIds::Setting;
public:
    Room();
    ~Room() override = default;

    void screenchange(const std::string& msg);
    void CheckItempickup();
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window)override;
};

