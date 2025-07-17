#include "stdafx.h"
#include "Title.h"
#include "SpriteGo.h"
#include "ResourceMgr.h"

Title::Title() :Scene(SceneIds::Title)
{
}

void Title::Init() 
{
	
	texIds.push_back("graphics/Titles/normal.png");
	fontIds.push_back("fonts/TerminusTTF-Bold.ttf");

	SpriteGo* titlebg = new SpriteGo("graphics/Titles/normal.png", "Titles");
	// 창 크기와 텍스처 크기 가져오기
	TEXTURE_MGR.Load("graphics/Titles/normal.png");
	titlebg->GetSprite().setTexture(TEXTURE_MGR.Get("graphics/Titles/normal.png"));
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	auto texture = titlebg->GetSprite().getTexture();
	if (texture == nullptr)
	{
		std::cerr << "Error: texture is nullptr!" << std::endl;
	}
	else
	{
		titlebg->SetScale(
			{
			FRAMEWORK.GetWindowSizeF().x / texture->getSize().x,
			FRAMEWORK.GetWindowSizeF().y / texture->getSize().y
			});
	}
	AddGameObject(titlebg);

	clickStart = (TextGo*)AddGameObject(new TextGo("fonts/TerminusTTF-Bold.ttf"));
	clickStart->SetString("Click to start");
	clickStart->SetCharacterSize(50);
	clickStart->SetFillColor(sf::Color::White);
	clickStart->SetPosition({ 100.0f, 100.f });

	messageText = new TextGo("fonts/TerminusTTF-Bold.ttf");
	messageText->SetCharacterSize(24);
	messageText->SetFillColor(sf::Color::White);
	messageText->SetPosition({ 50.f, 50.f }); // 적당한 화면 좌표
	messageText->sortingLayer = SortingLayers::UI;
	messageText->sortingOrder = 1;
	AddGameObject(messageText);

	Scene::Init();

}
void Title::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();
	messageText->SetString("");
	MUSIC_MGR.PlayBGM("Audio/BGM/MyBurdenIsLight.ogg");
	bgm.play();

}
void Title::Update(float dt)
{


	if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	{

		SCENE_MGR.ChangeScene(SceneIds::Room);
	}
	Scene::Update(dt);
}
void Title::Draw(sf::RenderWindow& window)
{
	auto defaultView = window.getView();
	window.setView(worldView);
	window.setView(uiView);
	Scene::Draw(window);
	window.setView(defaultView);
	
}

void Title::screenchange(const std::string& msg)
{
	if (screen == nullptr) // Check if modetitle is initialized
	{
		std::cerr << "Error: modetitle is not initialized!" << std::endl;
		return;
	}
}