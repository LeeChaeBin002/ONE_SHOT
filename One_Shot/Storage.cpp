#include "stdafx.h"
#include "Storage.h"

Storage::Storage(const std::string name) :GameObject(name)
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

	texId = "graphics/Menus/Storage.png";
	if (!TEXTURE_MGR.Exists(texId))
	{
		TEXTURE_MGR.Load(texId);
	}
	inventorybg.setTexture(TEXTURE_MGR.Get(texId));
	SetPosition({ 0.5f,0.0f });
	SetOrigin(Origins::TL);
	slots.clear();
	const float storageWidth = 200.f;  // Storage.png 가로 크기
	const float storageHeight = 300.f; // Storage.png 세로 크기
	const float startX = 45.f;
	const float startY = 120.f;
	const float offsetX = 280.f; // 두 슬롯 간 가로 거리
	const float offsetY = 30.f; // 두 슬롯 간 세로 거리

	for (int i = 0; i < 4; ++i)
	{
		std::string texPath = "graphics/Menus/empty_slot" + std::to_string(i + 1) + ".png";

		if (!TEXTURE_MGR.Load(texPath))
		{
			std::cerr << "Failed to load slot texture: " << texPath << std::endl;
		}
		SpriteGo* slot = new SpriteGo(texPath);
		slot->SetOrigin(Origins::MC);
		int row = i / 2;//0,0,1,1
		int col = i % 2;//0,1,0,1
		sf::Vector2f slotPos = { startX + col * offsetX, startY + row * offsetY };
		slot->SetPosition(slotPos);
		slot->GetSprite().setTexture(TEXTURE_MGR.Get(texPath));
		slot->SetScale({ 1.0f, 1.0f });
		//slot->GetSprite().setColor(sf::Color::White);
		std::cout << "SlotPos (" << slotPos.x << ", " << slotPos.y << ")" << std::endl;

		slots.push_back(slot);
	}
	selectedIndex = 0;
}

void Storage::Update(float dt)
{

	highlightTime += dt * highlightSpeed;
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
		sf::Color color = slot->GetSprite().getColor();
		if (i == selectedIndex)
		{
			sf::RectangleShape overlay(slot->GetSprite().getGlobalBounds().getSize());
			overlay.setPosition(slot->GetPosition());
			overlay.setOrigin(slot->GetSprite().getOrigin());

			float alpha = (std::sin(highlightTime) * 0.5f + 0.5f) * 200.f; // 최대 200의 알파
			overlay.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
			window.draw(overlay);
		}
		else
		{
			color.a = 255;
		}
		slot->GetSprite().setColor(color);
		//std::cout << "Slot Count: " << slots.size() << std::endl; // 여기!
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
		Utils::SetOrigin(inventorybg, preset);
	}

}

void Storage::AddItem(const std::string& texPath)
{
	if (!TEXTURE_MGR.Exists(texPath))
	{
		if (!TEXTURE_MGR.Load(texPath))
		{
			std::cerr << "Failed to load texture: " << texPath << std::endl;
			return;
		}
	}
	if (currentSlotIndex >= slots.size())
	{
		std::cout << "No empty slot available" << std::endl;
		return;
	}
	slots[currentSlotIndex]->GetSprite().setTexture(TEXTURE_MGR.Get(texPath));
	std::cout << "Added item to slot " << currentSlotIndex << std::endl;
	currentSlotIndex++;
}
