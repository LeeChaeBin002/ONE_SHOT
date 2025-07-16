#pragma once
#include "Scene.h"
class cellar2 :
    public Scene
{
protected:
	AniPlayer* player = nullptr;
	sf::Sound bgm;
	float offsetX = 28.f;
	float offsetY = 220.f;
	sf::Sprite background;
	bool positionSet = false;
	TextGo* messageText = nullptr;
	bool canAccesscellar = false;
	Cellar2State state = Cellar2State::Default;
	void UpdateSpritePosition();

	std::vector<sf::Texture*> textures;
	sf::Sprite sprite;

	int currentFrame = 0;
	float frameTime = 0.f;
	float frameDuration = 0.4f; // 프레임당 0.1초
	bool isPlaying = false;

public:
    cellar2();
    ~cellar2() override = default;

	void Init()override;
	void Enter()override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Release() override;
	void Exit()override;
	void InitAnimation();
	void PlayAnimation();
	

};

