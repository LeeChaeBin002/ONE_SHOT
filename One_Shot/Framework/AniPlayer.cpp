#include "stdafx.h"
#include "AniPlayer.h"

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

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "??" << std::endl;
		}
	);
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{


	animator.SetTarget(&body); // 애니메이터에 연결
	animator.Play("animations/idleNico.csv"); // 재생할 애니메이션
	SetPosition({ 0.f, 0.f });
	SetScale({ 1.f, 1.f });
	SetRotation(0.f);
	velocity = { 0.f, 0.f };
	isGrounded = true;


	std::cout << animator.GetCurrentClipId() << std::endl;

	animator.SetTarget(&body);

}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);

	float h = 0.f;

	if (isGrounded)
	{
		h = InputMgr::GetAxis(Axis::Horizontal);
		velocity.x = h * speed;
	}
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		velocity.y = -250.f;
		animator.Play("animations/jump.csv");
	}
	if (!isGrounded)
	{
		velocity += gravity * dt;
	}
	position += velocity * dt;
	if (position.y > 0.f)
	{
		velocity.y = 0.f;
		position.y = 0.f;
		isGrounded = true;
	}
	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.0f, 1.0) : sf::Vector2f(- 1.f, 1.0f));
	}

	// Ani
	if (animator.GetCurrentClipId() == "Idle")
	{
		if (h != 0.f)
		{
			animator.Play("animations/run.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Run")
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
	{
		if (h == 0.f)
		{
			animator.Play("animations/idle.csv");
		}
		else
		{
			animator.Play("animations/run.csv");
		}
	}
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
