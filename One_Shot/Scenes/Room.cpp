#include "stdafx.h"
#include "Room.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "SoundMgr.h"
#include "Storage.h"
#pragma execution_character_set("utf-8")


Room::Room() : Scene(SceneIds::Room)
{

}

void Room::Init()
{
	texIds.push_back("graphics/Pictures/Menus/empty_slot1.png");
	texIds.push_back("graphics/Pictures/Menus/empty_slot2.png");
	texIds.push_back("graphics/Pictures/Menus/empty_slot3.png");
	texIds.push_back("graphics/Pictures/Menus/empty_slot4.png");
	texIds.push_back("graphics/Menus/Storage.png");
	storage = (Storage*)AddGameObject(new Storage("graphics/Menus/Storage.png"));
	texIds.push_back("graphics/Pictures/ko/instruction1.png");
	texIds.push_back("graphics/Pictures/ko/instruction2.png");
	texIds.push_back("graphics/Pictures/ko/instruction3.png");
	texIds.push_back("graphics/Pictures/ko/instruction4.png");
	// instruction 이미지 로드
	for (int i = 1; i <= 4; ++i)
	{
		std::string texPath = "graphics/Pictures/ko/instruction" + std::to_string(i)+".png";
		SpriteGo* instruction = new SpriteGo(texPath);
		instruction->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y * 0.5f });
		instruction->SetOrigin(Origins::MC);
		if (!TEXTURE_MGR.Load(texPath))
		{
			std::cerr << "Failed to load instruction texture: " << texPath << std::endl;
		}
		else
		{
			auto texture = TEXTURE_MGR.Get(texPath);
			instruction->GetSprite().setTexture(texture);
			float scaleX = FRAMEWORK.GetWindowSizeF().x / texture.getSize().x;
			float scaleY = FRAMEWORK.GetWindowSizeF().y / texture.getSize().y;
			instruction->SetScale({ scaleX, scaleY });
		}
		instruction->SetActive(false); // 처음에는 안 보이게
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

	TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
	go->SetString("Room");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;
	AddGameObject(go);

	messageText = new TextGo("fonts/TerminusTTF-Bold.ttf");
	messageText->SetCharacterSize(24);
	messageText->SetFillColor(sf::Color::White);
	messageText->SetPosition({ 50.f, 50.f }); // 적당한 화면 좌표
	messageText->sortingLayer = SortingLayers::UI;
	messageText->sortingOrder = 1;
	AddGameObject(messageText);

	player = new AniPlayer("player");
	player->SetPosition({ 0.f,0.f });
	player->SetSpeed(100.f);
	player->SetAnimationSpeed(1.0f);
	player->Reset();
	player->ApplyStateTexture();
	AddGameObject(player);
	Scene::Init();
	
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

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
	player->ApplyStateTexture(); 
}
void Room::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		trigger = !trigger;
		if (storage)
			storage->SetActive(trigger);
	}
	if (storage && storage->GetActive())
	{
		storage->Update(dt);
	}
	Scene::Update(dt);

	//messageText->SetString("창문 밖에 뭔가 보인다");
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
			case 3:
				soundPath = "";
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
	/*if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{

		SCENE_MGR.ChangeScene(SceneIds::Storege);

	}*/
	// 기존 플레이어 이동, 체크 등등...
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
		if (playerPos.x >= 390 && playerPos.x <= 444 &&
			playerPos.y >= 160 && playerPos.y <= 163)
		{
			ShowMessage("hint:2817");
		}
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
	// �⺻ �� ����
	auto defaultView = window.getView();

	window.setView(worldView);

	for (auto obj : gameObjects)
	{
		obj->Draw(window);
	}
	

	// UI �׸���
	window.setView(uiView);

	Scene::Draw(window);

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
		delete storage;
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
				std::cout << "item1 get!" << std::endl;
			}
		}
	}

}

void Room::ShowMessage(const std::string& msg)
{
	if (messageText)
	{
		messageText->SetString(msg);
	}
}
void Room::Exit()
{
	
}