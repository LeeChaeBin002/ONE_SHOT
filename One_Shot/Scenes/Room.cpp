#include "stdafx.h"
#include "Room.h"
#include "Player.h"
#include "AniPlayer.h"
#include "SpriteGo.h"


Room::Room() :Scene(SceneIds::Room)
{

}

void Room::Init()
{
	
	texIds.push_back("graphics/Tilesets/niko_room.png");
	texIds.push_back("graphics/Icons/item_start_remote.png");
	texIds.push_back("graphics/Characters/niko.png");
	fontIds.push_back("resources/fonts/TerminusTTF-Bold.ttf");
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

	TextGo* go = new TextGo("resources/fonts/TerminusTTF-Bold.ttf");
	go->SetString("Room");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	//AddGameObject(go);

	AniPlayer* player=(new AniPlayer("player"));
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
	
	window.setView(defaultView);
	
}
void Room::screenchange(const std::string& msg)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}