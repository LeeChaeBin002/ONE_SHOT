#pragma once
#include "Scene.h"
class Stage1 :
    public Scene
{
protected:
	AniPlayer* player = nullptr;
	sf::Sound bgm;

	sf::Sprite background;
	bool positionSet = false;
	TextGo* messageText = nullptr;
public:
    Stage1();
    ~Stage1()override = default;
	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
	void ShowMessage(const std::string& msg);
	void Exit()override;
};

