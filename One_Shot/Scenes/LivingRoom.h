#pragma once
#include "Scene.h"
#include "AniPlayer.h"
#include "TextGo.h"
class Storge;

class LivingRoom : public Scene
{
protected:
	AniPlayer* player = nullptr;
	sf::Sound bgm;

	sf::Sprite background;
	bool positionSet = false;
	TextGo* messageText = nullptr;
	bool canAccessLivingRoom = false;
	Storage* storage = nullptr;
	SpriteGo* selectedIcon = nullptr;

public:
	LivingRoom();
	~LivingRoom()override=default;
	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
	void ShowMessage(const std::string& msg);
	void Exit()override;
	void RemoveSelectedIcon();
	
};

