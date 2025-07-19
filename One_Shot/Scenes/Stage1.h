#pragma once
#include "Scene.h"
enum class IntroState
{
	WaitingToStart,
	Playing,
	WaitingAfterEnd,
	Finished
};


class Stage1 :
    public Scene
{
protected:
	AniPlayer* player = nullptr;
	sf::Sound bgm;

	IntroState introState;
	float introTimer = 0.f;
	sf::Sprite background;
	bool positionSet = false;
	TextGo* messageText = nullptr;
	SpriteGo* introImage = nullptr;
	bool introFinished = false;
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
	void InitAnimation();
};

