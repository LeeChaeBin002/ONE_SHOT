#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texPlayerId, const std::string& name)
	: GameObject(name), textureId(texPlayerId)
{
	if (TEXTURE_MGR.Exists(texPlayerId))
	{
		sprite.setTexture(TEXTURE_MGR.Get(texPlayerId));
	}
	else
	{
		if (TEXTURE_MGR.Load(texPlayerId))
		{
			sprite.setTexture(TEXTURE_MGR.Get(texPlayerId));
		}
		else
		{
			std::cerr << "SpriteGo 생성: 텍스처 로드 실패 " << texPlayerId << std::endl;
		}
	}
}

void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
}

void SpriteGo::SetRotation(float rot)
{
	rotation = rot;
	sprite.setRotation(rotation);
}

void SpriteGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sprite.setScale(scale);
}

void SpriteGo::SetOrigin(const sf::Vector2f& o)
{
	originPreset = Origins::Custom;
	origin = o;
	sprite.setOrigin(o);
}

void SpriteGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(sprite, originPreset);
	}

}

void SpriteGo::SetTexture(const std::string& path)
{
	if (TEXTURE_MGR.Load(path))
	{
		sprite.setTexture(TEXTURE_MGR.Get(path));
	}
}

void SpriteGo::Init()
{
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(textureId));
	Utils::SetOrigin(sprite, originPreset);
}

void SpriteGo::Update(float dt)
{

}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(sprite);
	}
}
sf::FloatRect SpriteGo::GetGlobalBounds()const
{
	return sprite.getGlobalBounds();
}