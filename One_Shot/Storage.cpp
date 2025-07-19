#include "stdafx.h"
#include "Storage.h"
#include "Room.h"

Storage::Storage(const std::string name) :GameObject(name)
{

}
Storage& Storage::Instance()
{
	static Storage instance("Storage");
	return instance;
}
void Storage::Init()//씬당 한번씩
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	texId = "graphics/Menus/Storage.png";
	if (!TEXTURE_MGR.Exists(texId))
	{
		TEXTURE_MGR.Load(texId);
	}
	inventorybg.setTexture(TEXTURE_MGR.Get(texId));
	SetOrigin(Origins::TL);

	slots.clear();
	slotHasOverlay.clear();
	slotHasItem.clear();

	for (int i = 0; i < 4; ++i)
	{
		std::string texPath = "graphics/Menus/empty_slot" + std::to_string(i + 1) + ".png";

		if (!TEXTURE_MGR.Load(texPath))
		{
			std::cerr << "Failed to load slot texture: " << texPath << std::endl;
		}
		SpriteGo* slot = new SpriteGo(texPath);
		slot->SetOrigin(Origins::MC);
		slot->SetScale({ 1.0f, 1.0f });
		slotHasOverlay.push_back(false);
		slotHasItem.push_back(false);
		slots.push_back(slot);
	}

	SetPosition({ 0.f, 0.f });  // 반드시 슬롯 위치를 다시 배치
}

void Storage::Release()
{
}

void Storage::Reset()//초기화..
{
	currentSlotIndex = 0;
	selectedIndex = 0;
	highlightTime = 0.f;
}

void Storage::Update(float dt)
{
	for (int i = 0; i < slots.size(); ++i)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			std::cout << "슬롯 클릭: " << i << std::endl;
			if (onItemSelected)
			{
				onItemSelected(selectedIndex); // 이게 호출되어야 Room에서 아이콘 생성
			}
		}
	}

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

		// 기존 선택 슬롯 자주색 해제 + 원래 슬롯 이미지 복구
		if (selectedSlotIndex >= 0 && selectedSlotIndex < slotHasOverlay.size())
		{
			slotHasOverlay[selectedSlotIndex] = false;
		}
		// 새로 선택한 슬롯 업데이트
		selectedSlotIndex = selectedIndex;
		if (selectedSlotIndex >= 0 && selectedSlotIndex < slotHasOverlay.size())
		{
			slotHasOverlay[selectedSlotIndex] = true;
		}

		if (slotHasItem[selectedIndex])
		{
			if (onItemSelected)
			{
				onItemSelected(selectedIndex);
			}
		}
		else
		{
			if (onRemoveSelectedIcon)
			{
				onRemoveSelectedIcon();  // 빈 슬롯 선택 시 아이콘 제거
			}
		}
	}
}

void Storage::Draw(sf::RenderWindow& window)
{
	window.draw(inventorybg);

	for (size_t i = 0; i < slots.size(); ++i)
	{
		SpriteGo* slot = slots[i];
		if (slot == nullptr) continue;


		if (slotHasOverlay[i]&& slot->GetSprite().getTexture() != nullptr)
		{
			sf::RectangleShape overlay(slot->GetSprite().getGlobalBounds().getSize());
			overlay.setPosition(slot->GetPosition());
			overlay.setOrigin(slot->GetSprite().getOrigin());
			overlay.setFillColor(sf::Color(60, 0, 40, 180));  // 진한 자주색
			window.draw(overlay);
		}

		if (i == selectedIndex)
		{
			sf::FloatRect bounds = slot->GetGlobalBounds();
			sf::RectangleShape border({ bounds.width, bounds.height });
			border.setPosition({ bounds.left, bounds.top });
			border.setFillColor(sf::Color::Transparent);
			border.setOutlineThickness(3.f);
			border.setOutlineColor(sf::Color::Yellow);
			window.draw(border);
		}
		window.draw(slot->GetSprite());

	}
}

void Storage::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	inventorybg.setPosition(pos);
	const float startX = 170.f;
	const float startY = 130.f;
	const float offsetX = 280.f;
	const float offsetY = 30.f;

	for (int i = 0; i < slots.size(); ++i)
	{
		int row = i / 2;
		int col = i % 2;
		sf::Vector2f slotPos = { pos.x + startX + col * offsetX,
								 pos.y + startY + row * offsetY };
		slots[i]->SetPosition(slotPos);
	}
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
	if(!TEXTURE_MGR.Exists(texPath))
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
	slotHasItem[currentSlotIndex] = true;

	selectedIndex = currentSlotIndex;
	selectedSlotIndex = currentSlotIndex;
	slotHasOverlay[currentSlotIndex] = true;

	if (onItemSelected)
	{
		std::cout << "onItemSelected 호출됨! index: " << currentSlotIndex << std::endl;
		onItemSelected(currentSlotIndex);
	}
	else
	{
		std::cout << "onItemSelected가 nullptr임" << std::endl;
	}

	currentSlotIndex++;
	
}

void Storage::TriggerSelect()
{
	for (int i = 0; i < slots.size(); ++i)
	{
		if (onItemSelected)
		{
			onItemSelected(i);
		}
	}
}
