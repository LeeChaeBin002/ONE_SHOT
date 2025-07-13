#include "stdafx.h"
#include "AniPlayer.h"
#include "Animator.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name)
{

}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()

{
	body.setOrigin(24.f, 32.f); // 48 / 2, 64 / 2
	TEXTURE_MGR.Load("graphics/Characters/niko.png");
	body.setTexture(TEXTURE_MGR.Get("graphics/Characters/niko.png"));
	body.setTextureRect(sf::IntRect(0, 0, 48, 64)); // x, y, width, height

	ANI_CLIP_MGR.Load("animations/idleNico.csv");
	ANI_CLIP_MGR.Load("animations/runRight.csv");
	ANI_CLIP_MGR.Load("animations/runLeft.csv");
	ANI_CLIP_MGR.Load("animations/runDown.csv");
	ANI_CLIP_MGR.Load("animations/runUp.csv");

	animator.SetTarget(&body); // 애니메이터에 연결
	animator.Play("idle");
	


	SetPosition({ 0.f, 0.f });
	SetScale({ 1.f, 1.f });
	SetRotation(0.f);
	velocity = { 0.f, 0.f };


}

void AniPlayer::Update(float dt)
{

	//animator.Update(dt);

	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v = InputMgr::GetAxis(Axis::Vertical);
	velocity.x = h * speed;
	velocity.y = v * speed;

	position += velocity * dt;
	SetPosition(position);



	// Animation timing
	animationTime += dt;
	const float frameDuration = 0.1f; // 시간당 프레임 변경 속도 (초)
	if (animationTime >= frameDuration)
	{
		animationTime = 0.f;
		currentFrame = (currentFrame + 1) % 4; // 4프레임 순환
	}

	int frameX = currentFrame * 48;
	int frameY = 0;

	if (h > 0)
	{
		SetScale({ -1.f, 1.f });
		frameY = 64; // Right
	}
	else if (h < 0)
	{
		SetScale({ 1.f, 1.f });
		frameY = 64; // Left (반전)
	}
	else if (v < 0)
	{
		frameY = 192; // Up row
	}
	else if (v > 0)
	{
		frameY = 0; // Down row
	}
	
	else
	{
		frameX = 0;
		frameY = 0; // Idle
	}

	body.setTextureRect(sf::IntRect(frameX, frameY, 48, 64));
}


void AniPlayer::Draw(sf::RenderWindow& window)
{
	if (body.getTexture() == nullptr)
	{
		std::cerr << "ERROR: 텍스처가 설정되지 않았습니다 (nullptr)." << std::endl;
		return; // 예외 방지
	}
		window.draw(body);
}
