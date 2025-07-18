#include "stdafx.h"
#include "Room.h"
#include "Player.h"
#include "AniPlayer.h"

Room::Room() :Scene(SceneIds::Room)
{

}

void Room::Init()
{

	texIds.push_back("graphics/Characters/niko.png");
	fontIds.push_back("resources/fonts/TerminusTTF-Bold.ttf");
	// 이때 한 번만 로드
	if (!ANI_CLIP_MGR.Exists("idleNico")) // 존재 확인 후 로드
	{
		ANI_CLIP_MGR.Load("animations/idleNico.csv");
	}

	TextGo* go = new TextGo("resources/fonts/TerminusTTF-Bold.ttf");
	go->SetString("Room");
	go->SetCharacterSize(30);
	go->SetFillColor(sf::Color::White);
	go->sortingLayer = SortingLayers::UI;
	go->sortingOrder = 0;

	AddGameObject(go);

	AniPlayer* player=(new AniPlayer("player"));
	player->SetPosition({ 0.f,-200.f });
	player->Reset();
	AddGameObject(player);

}
void Room::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, -200.f });

	Scene::Enter();

}
void Room::Update(float dt)
{
	Scene::Update(dt);
}

void Room::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
void Room::screenchange(const std::string& msg)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}