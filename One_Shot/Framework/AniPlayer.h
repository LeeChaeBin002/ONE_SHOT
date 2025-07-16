#pragma once
#include "Animator.h"
#include "GameObject.h"

class AniPlayer : public GameObject
{
protected:
	AniPlayer* player = nullptr;
	sf::Sprite body;
	Animator animator;
	sf::Sprite sprite;
	bool isAnimating = true;
	sf::Texture* currentTexture = nullptr;

	sf::Vector2f gravity = { 0.f, 0.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
	float speed = 200.f;
	float animationTime = 0.f;  // 애니메이션 경과 시간
	int currentFrame = 0;

public:
	static bool hasBulb;
	sf::Sprite& GetSprite() { return sprite; }
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void play(const std::string& animationId);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetSpeed(float s) { speed = s; }
	void SetAnimationTexture(const sf::Texture& texture);
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
	sf::FloatRect GetGlobalBounds()const override;
	void SetStaticTexture(const sf::Texture& texture);
	void ApplyStateTexture();
};
