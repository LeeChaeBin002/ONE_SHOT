#include "stdafx.h"
#include "Room.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "SoundMgr.h"
#pragma execution_character_set("utf-8")


Room::Room() :Scene(SceneIds::Room)
{

}

void Room::Init()
{
	
	texIds.push_back("graphics/Tilesets/niko_room.png");
	texIds.push_back("graphics/Icons/item_start_remote.png");
	texIds.push_back("graphics/Characters/niko.png");
	fontIds.push_back("fonts/TerminusTTF-Bold.ttf");
	
	// �̶� �� ���� �ε�
	if (!ANI_CLIP_MGR.Exists("idleNico")) // ���� Ȯ�� �� �ε�
	{
		ANI_CLIP_MGR.Load("animations/idleNico.csv");
	}
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
	player->SetPosition({ 0.f,100.f });
	player->Reset();
	AddGameObject(player);
	Scene::Init();
	
}
void Room::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);
	Scene::Enter();
	// ���⼭ ĳ����, �������� ��ġ ���� ����

	messageText->SetString("");
	SOUNDBUFFER_MGR.Load("Audio/BGM/SomeplaceIKnow.ogg");
	bgm.setBuffer(SOUNDBUFFER_MGR.Get("Audio/BGM/SomeplaceIKnow.ogg"));
	bgm.setLoop(true);
	bgm.play();
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == "player")
		{
			AniPlayer* player = dynamic_cast<AniPlayer*>(obj);
			if (player)
			{
				player->Reset();
			}
		}
	}

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
	
}
void Room::Update(float dt)
{// ù ��° Update������ ��ġ ����
	//messageText->SetString("창문 밖에 뭔가 보인다");

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
			std::cout << "LivingRoom 이동!" << std::endl;
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

	window.setView(defaultView);
	
}
void Room::Release()
{
	bgm.stop();
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
