#include "stdafx.h"
#include "Storage.h"

Storage::Storage(const std::string name):GameObject(name)
{
	
}

void Storage::Init()//씬당 한번씩
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void Storage::Release()
{
}

void Storage::Reset()//초기화..
{
	
	texId= "graphics/Menus/Storage.png";
	inventorybg.setTexture(TEXTURE_MGR.Get(texId));
	SetPosition({ 0.f,0.f });
	SetOrigin(Origins::TL);
}

void Storage::Update(float dt)
{
}

void Storage::Draw(sf::RenderWindow& window)
{
	window.draw(inventorybg);
}

void Storage::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	inventorybg.setPosition(pos);
}

void Storage::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	inventorybg.setRotation(rot);
}

void Storage::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	inventorybg.setScale(s);
}

void Storage::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	inventorybg.setOrigin(o);
}

void Storage::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(inventorybg,preset);
	}

}
