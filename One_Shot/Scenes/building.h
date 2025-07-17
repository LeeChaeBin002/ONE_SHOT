#pragma once
#include "Scene.h"
class building :
    public Scene
{
protected:
	
	AniPlayer* player = nullptr;
	sf::Sound bgm;

	sf::Sprite background;
	bool positionSet = false;
	TextGo* messageText = nullptr;
public:
    building();
    ~building()override = default;
	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
	void ShowMessage(const std::string& msg);
	void Exit()override;
};

