#pragma once
#include "Animator.h"

class AniPlayer : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	

	sf::Vector2f gravity = { 0.f, 0.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
	float speed = 500.f;
	float animationTime = 0.f;  // 애니메이션 경과 시간
	int currentFrame = 0;

public:
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

};
