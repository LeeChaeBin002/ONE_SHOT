#include "stdafx.h"
#include "Room.h"
#include "Player.h"
#include "AniPlayer.h"

Room::Room() :Scene(SceneIds::Room)
{

}

void Room::Init()
{
	texIds.push_back("graphics/niko.png");
	fontIds.push_back("resources/fonts/TerminusTTF-Bold.ttf");
	
	ANI_CLIP_MGR.Load("animations/idleNico.csv");

	//TextGo* go = new TextGo("resources/fonts/DS-DIGIT.ttf");
	//go->SetString("Room");
	//go->SetCharacterSize(30);
	//go->SetFillColor(sf::Color::White);
	//go->sortingLayer = SortingLayers::UI;
	//go->sortingOrder = 0;

	//AddGameObject(go);

	AniPlayer* player=(new AniPlayer("player"));
	player->SetPosition({ 0.f,-200.f });
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
	worldView.setCenter({ 0.f, -200.f });
	//tileManager
	if (!tileMgr.Load("maps/red_start.png", "maps/room.csv"))
	{
		std::cerr << "타일 로드 실패!" << std::endl;
		return;
	}

	wall = tileMgr.GetSprite("Red Wall Tile");
	bed = tileMgr.GetSprite("Bed (Pillow + Blanket)");

	wall.setPosition(100.f, 100.f);
	bed.setPosition(140.f, 100.f);

	//Scene::Enter();

}
void Room::Update(float dt)
{
	Scene::Update(dt);
	
}
void Room::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(wall);
	window.draw(bed);
}
void Room::screenchange(const std::string& msg)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}