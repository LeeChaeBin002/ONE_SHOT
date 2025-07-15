#include "stdafx.h"
#include "Title.h"
#include "SpriteGO.h"
#include "ResourceMgr.h"

void Title::screenchange(const std::string& msg)
{
	if (screen == nullptr) // Check if modetitle is initialized
	{
		std::cerr << "Error: modetitle is not initialized!" << std::endl;
		return;
	}
}
void Title::Init() 
{
	texIds.push_back("resources/background.png");
	fontIds.push_back("fonts/TerminusTTF-Bold.ttf");
}
void Title::Enter()
{
	Scene::Enter();
	SpriteGo* bg = new SpriteGo("resources/background.png", "Background");
	AddGameObject(bg);
	bg->Init();
	const sf::Texture* bgTex = bg->GetSprite().getTexture();
	if (!bgTex)
	{
		std::cerr << "배경 텍스쳐가 설정되지않았습니다!" << std::endl;
		return;
	}

	bg->SetOrigin(Origins::TL);
	bg->SetPosition({ 0.f,0.f });

	sf::Vector2f winSize = FRAMEWORK.GetWindowSizeF();
	sf::Vector2u texSize = bgTex->getSize();
	bg->SetScale({ winSize.x / texSize.x,winSize.y / texSize.y });

	clickStart = (TextGo*)AddGameObject(new TextGo("fonts/TerminusTTF-Bold.ttf"));
	clickStart->SetString("Click to start");
	clickStart->SetCharacterSize(50);
	clickStart->SetFillColor(sf::Color::White);
	clickStart->SetPosition({ 800.0f, 850.f });

	const sf::Font& font = FONT_MGR.Get("fonts/TerminusTTF-Bold.ttf");
	if (FONT_MGR.IsEmpty(font))
	{
		std::cerr << "폰트 로딩 실패: --" << std::endl;
	}
	else
	{
		screen->GetText().setFont(font);
		clickStart->GetText().setFont(font);
		
	} 
}
void Title::Update(float dt)
{

}
void Title::Draw(sf::RenderWindow& window)
{

}
