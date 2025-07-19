#include "stdafx.h"
#include "Room.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "SoundMgr.h"
#include "Storage.h"
#include "SceneBase.h"
#include "GameState.h"
#pragma execution_character_set("utf-8")


Room::Room() : Scene(SceneIds::Room)
{

}

void Room::Init()
{
	storage = &Storage::Instance();

	if (!storage->IsInitialized())
	{
		storage->Init();
		storage->SetActive(false);
		storage->Reset();
	}
	AddGameObject(storage);

	
	storage->onItemSelected = [this](int index)
		{
			RemoveSelectedIcon();
			std::cout << "Room에서 onItemSelected 호출됨 index: " << index << std::endl;
			// 오른쪽 아래에 아이콘 생성
			std::string iconPath = "graphics/Icons/item_start_remote.png";
			if (!TEXTURE_MGR.Exists(iconPath))
			{
				if (!TEXTURE_MGR.Load(iconPath))
				{
					std::cerr << "Failed to load icon texture: " << iconPath << std::endl;
					return;
				}
			}
			const sf::Texture& tex = TEXTURE_MGR.Get(iconPath);

			std::cout << "selectedIcon 텍스처 size: "
				<< tex.getSize().x << ", " << tex.getSize().y << std::endl;
			// 기존 아이콘 있으면 삭제
			storage->onRemoveSelectedIcon = [this]()
				{
					RemoveSelectedIcon();
				};
			if (selectedIcon != nullptr)
			{
				selectedIcon->SetActive(false);
				gameObjects.remove(selectedIcon); 
				delete selectedIcon;
				selectedIcon = nullptr;
			}
			SpriteGo* icon = new SpriteGo(iconPath,"RemoteIcon");
			sf::Texture& texPlayerId = TEXTURE_MGR.Get(iconPath);
			icon->GetSprite().setTexture(texPlayerId);
			sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
			icon->SetPosition({ windowSize.x -50.f, windowSize.y - 50.f }); // 오른쪽 아래
			icon->SetScale({ 1.5f, 1.5f });
			icon->SetOrigin(Origins::MC);
			//icon->SetPosition({ 300.f, 200.f });
			icon->SetActive(true);
			AddGameObject(icon);
			selectedIcon = icon;

			std::cout << "selectedIcon Position: "
				<< selectedIcon->GetPosition().x << ", "
				<< selectedIcon->GetPosition().y << std::endl;
		};
	
	
	texIds.push_back("graphics/Pictures/ko/instruction1.png");
	texIds.push_back("graphics/Pictures/ko/instruction2.png");
	texIds.push_back("graphics/Pictures/ko/instruction3.png");
	texIds.push_back("graphics/Pictures/ko/instruction4.png");
	// instruction 이미지 로드
	for (int i = 1; i <= 4; ++i)
	{
		std::string texPath = "graphics/Pictures/ko/instruction" + std::to_string(i) + ".png";

		if (!TEXTURE_MGR.Exists(texPath))
		{
			if (!TEXTURE_MGR.Load(texPath))
			{
				std::cerr << "Failed to load instruction texture: " << texPath << std::endl;
				continue;
			}
		}

		SpriteGo* instruction = new SpriteGo(texPath);
		instruction->SetOrigin(Origins::MC); // 이미지 중심 기준
		instruction->SetPosition(FRAMEWORK.GetWindowSizeF() * 0.5f); // 화면 중심

		const sf::Texture& texture = TEXTURE_MGR.Get(texPath);

		float scaleX = FRAMEWORK.GetWindowSizeF().x / texture.getSize().x;
		float scaleY = FRAMEWORK.GetWindowSizeF().y / texture.getSize().y;

		float scale = std::min(scaleX, scaleY); // 창 크기 기준 80% 크기
		instruction->SetScale({ scale, scale });

		instruction->SetActive(false); // 처음엔 비활성
		AddGameObject(instruction);
		instructions.push_back(instruction);
	}
	// 아이템 슬롯 로드
	

	texIds.push_back("graphics/Tilesets/niko_room.png");
	texIds.push_back("graphics/Icons/item_start_remote.png");
	texIds.push_back("graphics/Characters/niko.png");
	fontIds.push_back("fonts/TerminusTTF-Bold.ttf");
	
	// niko_room.png�� ������� �߰�
	SpriteGo* roomBg = new SpriteGo("graphics/Tilesets/niko_room.png","NikoRoom");
	roomBg->SetPosition({ 0.f, 0.f }); // �ʿ��� ��ġ�� ����
	AddGameObject(roomBg);

	SpriteGo* remote = new SpriteGo("graphics/Icons/item_start_remote.png", "item1");
	remote->SetPosition({ 0.f, 0.f }); // �ʿ��� ��ġ�� ����
	AddGameObject(remote);


	player = new AniPlayer("player");
	player->SetPosition({ 0.f,0.f });
	player->SetSpeed(100.f);
	player->SetAnimationSpeed(1.0f);
	player->Reset();
	player->ApplyStateTexture();
	AddGameObject(player);
	Scene::Init();
	storage->SetActive(false);
	storage->Reset();

	messageText = new TextGo("fonts/TerminusTTF-Bold.ttf");
	messageText->Init();
	messageText->SetCharacterSize(24);
	messageText->SetFillColor(sf::Color::White);
	messageText->SetPosition({ 50.f, 50.f });
	messageText->sortingLayer = SortingLayers::UI;
	messageText->sortingOrder = 1;
	AddGameObject(messageText);
}
void Room::Enter()
{
	// 기존 코드
	Scene::Enter();
	

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
	if (SCENE_MGR.GetPreviousScene() == SceneIds::Title)
	{
		isShowingInstruction = true;
		instructionIndex = 0;

		if (!instructions.empty())
		{
			instructions[instructionIndex]->SetActive(true);
		}
		MUSIC_MGR.StopBGM();  // 기존 BGM 중단
	}
	else
	{
		isShowingInstruction = false;
		MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");
	
	}


	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);
	positionSet = false;

	


	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	
	player->ApplyStateTexture();
	Scene::Enter();
	// ���⼭ ĳ����, �������� ��ġ ���� ����
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == "player")
		{
			AniPlayer* player = dynamic_cast<AniPlayer*>(obj);
			if (player)
			{
				player->Reset();
				player->ApplyStateTexture(); 
			}
		}
	}
	for (const auto& itemPath : GameState::inventoryItems)
	{
		storage->AddItem(itemPath);
	}

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
	player->ApplyStateTexture(); 
}
void Room::Update(float dt)
{
	if (isShowingInstruction)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			// 페이지별 효과음 파일 경로 설정
			std::string soundPath;
			switch (instructionIndex)
			{
			case 0:
				soundPath = "Audio/ME/instruction1.wav";
				break;
			case 1:
				soundPath = "Audio/ME/instruction2.wav";
				break;
			case 2:
				soundPath = "Audio/ME/instruction3.wav";
				break;
			default:
				soundPath = "";
				break;
			}

			if (!soundPath.empty())
			{
				if (!SOUNDBUFFER_MGR.Exists(soundPath))
				{
					SOUNDBUFFER_MGR.Load(soundPath);
				}
				instructionEffect.setBuffer(SOUNDBUFFER_MGR.Get(soundPath));
				instructionEffect.play();
			}

			instructions[instructionIndex]->SetActive(false); // 현재꺼 끄고
			instructionIndex++;

			if (instructionIndex < instructions.size())
			{
				instructions[instructionIndex]->SetActive(true);
			}
			else
			{
				isShowingInstruction = false; // 전부 다 봤음
				MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");
			}
		}

		return; // instruction 보는 중엔 다른 Update 로직 실행 XX
	}
	
	if (InputMgr::GetKeyDown(sf::Keyboard::S))
	{
		trigger = !trigger;
		if (storage)
			storage->SetActive(trigger);
		std::cout << "Storage Active: " << trigger << std::endl;
	}
	if (storage && storage->GetActive())
	{
		storage->Update(dt);
		return;
	}
	Scene::Update(dt);
	if (!player) return;

	sf::Vector2f playerPos = player->GetPosition();
	// 컴퓨터 앞 위치 범위 (약간의 오차 허용)
	if (playerPos.x >= 230 && playerPos.x <= 270 &&
		playerPos.y >= 150 && playerPos.y <= 190)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
		
			SCENE_MGR.ChangeScene(SceneIds::Computer);
		}
	}

	if (!positionSet)
	{
		for (auto obj : gameObjects)
		{
			if (obj->GetName() == "player")
			{
				obj->SetPosition({ 300.f, 200.f });
			}
			else if (obj->GetName() == "item1")
			{
				obj->SetPosition({ 400.f, 250.f });
			}
		}
		positionSet = true;
	}

	CheckItempickup();

	if (hasRemote)
	{
		sf::Vector2f playerPos = player->GetPosition();
		if (playerPos.x >= 380 && playerPos.x <= 450 &&
			playerPos.y >= 150 && playerPos.y <= 170)
		{
			std::cout << "ShowMessage called, hasRemote: " << hasRemote << std::endl;
			ShowMessage("hint:2817");
		}
		
	}
	if (hasRemote && storage != nullptr && !remoteAddedToStorage)
	{
		storage->AddItem("graphics/Icons/item_start_remote.png");
		//GameState::inventoryItems.push_back("graphics/Icons/item_start_remote.png");  // 추가!
		if (storage->onItemSelected)
		{
			storage->onItemSelected(storage->GetCurrentSlotIndex() - 1);  // 방금 추가한 슬롯
		}
		remoteAddedToStorage = true;
	}

	if (canAccessLivingRoom && InputMgr::GetKeyDown(sf::Keyboard::Z))
	{
		if (playerPos.x >= 306 && playerPos.x <= 338 &&
			playerPos.y >= 280 && playerPos.y <= 333)
		{
			std::cout << "LivingRoom movement!" << std::endl;
			SCENE_MGR.ChangeScene(SceneIds::LivingRoom);
		}
		
	}

	Scene::Update(dt);
}

void Room::Draw(sf::RenderWindow& window)
{

	auto defaultView = window.getView();

	window.setView(worldView);

	for (auto obj : gameObjects)
	{
		if (obj == nullptr) continue;
		//std::cout << "Drawing object: " << obj << ", name: " << obj->GetName() << std::endl;
		try
		{
			obj->Draw(window);
		}
		catch (...)
		{
			std::cerr << "Draw 예외 발생: " << obj << std::endl;
		}
	}
	if (selectedIcon && selectedIcon->GetActive())
	{
		//std::cout << "selectedIcon 그리는 중!" << std::endl;
		selectedIcon->Draw(window);
	}

	// UI �׸���
	window.setView(uiView);

	Scene::Draw(window);
	if (storage && storage->GetActive())
	{
		storage->Draw(window);
	}

	if (messageText != nullptr && messageText->GetActive())
	{
		messageText->Draw(window);
		
	}
	// instruction 그리기
	if (isShowingInstruction && instructionIndex < instructions.size())
	{
		instructions[instructionIndex]->Draw(window);
	}

	window.setView(defaultView);
	
}
void Room::Release()
{
	if (storage != nullptr)
	{
		// gameObjects에서도 제거
		for (auto it = gameObjects.begin(); it != gameObjects.end(); )
		{
			if (*it == storage)
			{
				delete* it;
				it = gameObjects.erase(it);
			}
			else
			{
				++it;
			}
		}

		storage = nullptr;
	}
}

void Room::screenchange(const std::string& msg)
{
	
}

void Room::CheckItempickup()
{
	if (!player) return;

	for (auto obj : gameObjects)
	{
		if (obj->GetName() == "item1" && obj->GetActive())
		{
			sf::FloatRect playerBounds = player->GetGlobalBounds();
			sf::FloatRect itemBounds = obj->GetGlobalBounds();

			if (playerBounds.intersects(itemBounds))
			{
				obj->SetActive(false); // 아이템 비활성화
				hasRemote = true;
				//remoteAddedToStorage = true;
				std::cout << "item1 get! hasRemoste" <<hasRemote<< std::endl;

				std::string itemPath = "graphics/Icons/item_start_remote.png";
				if (std::find(GameState::inventoryItems.begin(), GameState::inventoryItems.end(), itemPath) == GameState::inventoryItems.end())
				{
				GameState::inventoryItems.push_back("graphics/Icons/item_start_remote.png");
				}
				if (storage != nullptr && !remoteAddedToStorage)
				{
					storage->AddItem(itemPath);
					remoteAddedToStorage = true;
				};
			}
		}
	}
}

void Room::ShowMessage(const std::string& msg)
{
	if (messageText)
	{
		messageText->SetString(msg);
		messageText->SetActive(true);
		//std::cout << "ShowMessage: " << msg << " 활성화" << std::endl;
	}
}
void Room::Exit()
{
	
}



void Room::RemoveSelectedIcon()
{
	if (selectedIcon)
    {
        selectedIcon->SetActive(false);

        // 안전하게 erase로 제거
        for (auto it = gameObjects.begin(); it != gameObjects.end(); )
        {
            if (*it == selectedIcon)
            {
                delete *it;
                it = gameObjects.erase(it);
				break;
            }
            else
            {
                ++it;
            }
        }

        selectedIcon = nullptr;
		
    }
}


