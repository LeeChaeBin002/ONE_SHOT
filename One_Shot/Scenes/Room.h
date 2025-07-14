#pragma once
#include "Scene.h"
#include "Room.h"
#include "TextGo.h"

class Room :
    public Scene
{
protected:

    AniPlayer* player = nullptr;
    sf::Sound bgm;
    
    sf::Sprite background;
    bool positionSet = false;
    bool hasRemote = false;
    bool ShowedWindowMsg = false;
  
    TextGo* messageText = nullptr;
    TextGo* screen;
    TextGo* clickStart;
    SceneIds changeScene = SceneIds::Setting;

public:
    Room();
    ~Room() override = default;

    void CheckItempickup();
    void ShowMessage(const std::string& msg);
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window)override;
    void Release() override;
    void screenchange(const std::string& msg);
};

