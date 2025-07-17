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
	slots.clear();

	const float startX = FRAMEWORK.GetWindowSizeF().x * 0.4f;
	const float startY = FRAMEWORK.GetWindowSizeF().y * 0.4f;
	const float offsetX = 100.f;  // 가로 간격
	const float offsetY = 100.f;  // 세로 간격

	for (int i = 1; i <= 4; ++i)
	{
		std::string texPath = "graphics/Pictures/Menus/empty_slot" + std::to_string(i+1) + ".png";
		TEXTURE_MGR.Load(texPath);
		SpriteGo* slot = new SpriteGo(texPath);
		slot->SetOrigin(Origins::MC);
		int row = i / 2;
		int col = i % 2;
		sf::Vector2f slotPos = { startX + col * offsetX, startY + row * offsetY };
		slot->SetPosition(slotPos);
		slot->SetScale({ 1.f, 1.f });

		slots.push_back(slot);
	}
	selectedIndex = 0;
}

void Storage::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		if (selectedIndex % 2 > 0)
			selectedIndex--;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		if (selectedIndex % 2 < 1)
			selectedIndex++;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		if (selectedIndex - 2 >= 0)
			selectedIndex -= 2;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		if (selectedIndex + 2 < slots.size())
			selectedIndex += 2;
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		std::cout << "Selected Slot: " << selectedIndex << std::endl;
		// 슬롯 선택 로직
	}
}

void Storage::Draw(sf::RenderWindow& window)
{
	window.draw(inventorybg);

	for (size_t i = 0; i < slots.size(); ++i)
	{
		SpriteGo* slot = slots[i];
		if (slot == nullptr) continue;

		window.draw(slot->GetSprite());
		if (i == selectedIndex)
		{
			sf::RectangleShape highlight(slot->GetSprite().getGlobalBounds().getSize());
			highlight.setPosition(slot->GetPosition());
			highlight.setFillColor(sf::Color::Transparent);
			highlight.setOutlineColor(sf::Color::White);
			highlight.setOutlineThickness(2.f);
			window.draw(highlight);
		}
		
	}
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
