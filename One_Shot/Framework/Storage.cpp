#include "stdafx.h"
#include "Storage.h"


Storage::Storage():Scene(SceneIds::Storege)
{

}
void Storage::Init()
{   
    TEXTURE_MGR.Load("graphics/Tilesets/Storage.png");
    inventoryBg.setTexture(TEXTURE_MGR.Get("graphics/UI/inventory_bg.png"));
    inventoryBg.setPosition({ 0.f, 0.f });
	
	SOUNDBUFFER_MGR.Load("Audio/SE/menu_decision.wav");

    items = { "item_start_remote.png", " ", " " };
    selectedIndex = 0;

    selectedText = new TextGo("fonts/TerminusTTF-Bold.ttf");
    selectedText->SetCharacterSize(24);
    selectedText->SetFillColor(sf::Color::White);
    selectedText->SetPosition({ 100.f, 100.f });
    selectedText->sortingLayer = SortingLayers::UI;
    AddGameObject(selectedText);

    UpdateSelectionText();
}
void Storage::Enter()
{
	Scene::Enter();
    sf::Sound sound;
    sound.setBuffer(SOUNDBUFFER_MGR.Get("Audio/SE/menu_decision.wav"));
    sound.play();
}
void Storage::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::Up))
    {
        if (selectedIndex > 0)
            selectedIndex--;
        UpdateSelectionText();
    }
    else if (InputMgr::GetKeyDown(sf::Keyboard::Down))
    {
        if (selectedIndex < items.size() - 1)
            selectedIndex++;
        UpdateSelectionText();
    }
}
void Storage::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
}
void Storage::Release()
{

}
void Storage::screenchange(const std::string& msg)
{

}
void Storage::Exit()
{

}

void Storage::UpdateSelectionText()
{
    std::string display;
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (i == selectedIndex)
            display += "> ";
        else
            display += "  ";

        display += items[i] + "\n";
    }
    selectedText->SetString(display);
}
