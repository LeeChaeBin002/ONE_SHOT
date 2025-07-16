#pragma once
#include "Scene.h"
#include "SpriteGo.h"
class cellar : public Scene
{
protected:
    
    AniPlayer* player = nullptr;
    sf::Sound bgm;
    SpriteGo* cellarBg = nullptr;

    sf::Sprite background;
    bool positionSet = false;
    TextGo* messageText = nullptr;
    bool canAccessLivingRoom = false;
public:
	cellar();
	~cellar()override=default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window)override;
    void Release() override;
    void screenchange(const std::string& msg);
    void Exit()override;


};

