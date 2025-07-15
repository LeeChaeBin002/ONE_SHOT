#include "stdafx.h"
#include "livingRoom.h"

LivingRoom::LivingRoom() : Scene(SceneIds::LivingRoom)
{
}
void LivingRoom::Init()
{
    texIds.push_back("graphics/Tilesets/living_room.png");  // 예시 배경
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");

    SpriteGo* roomBg = new SpriteGo("graphics/Tilesets/living_room.png", "LivingRoomBg");
    roomBg->SetOrigin(Origins::TL);
    roomBg->SetPosition({ 0.f, 0.f });
    AddGameObject(roomBg);

    //룸 이어서 노래 재생
    SOUNDBUFFER_MGR.Load("Audio/BGM/SomeplaceIKnow.ogg");
    bgm.setBuffer(SOUNDBUFFER_MGR.Get("Audio/BGM/SomeplaceIKnow.ogg"));
    bgm.setLoop(true);
    bgm.play();

    messageText = new TextGo("fonts/TerminusTTF-Bold.ttf");
    messageText->Init();
    messageText->SetCharacterSize(24);
    messageText->SetFillColor(sf::Color::White);
    messageText->SetPosition({ 50.f, 700.f });
    messageText->sortingLayer = SortingLayers::UI;
    messageText->sortingOrder = 1;
    AddGameObject(messageText);

    player = new AniPlayer("player");
    player->SetPosition({ 100.f, 300.f });
    player->Reset();
    AddGameObject(player);

    Scene::Init();
}

void LivingRoom::Enter()
{
    Scene::Enter();

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    
}

void LivingRoom::Update(float dt)
{
    Scene::Update(dt);

    if (!positionSet)
    {
        player->SetPosition({ 200.f, 300.f });
        positionSet = true;
    }

    if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    {
        SCENE_MGR.ChangeScene(SceneIds::Room);  // 예시: 방으로 돌아가기
    }
}

void LivingRoom::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);
}

void LivingRoom::Release()
{
    bgm.stop();
}

void LivingRoom::ShowMessage(const std::string& msg)
{
    if (messageText)
    {
        messageText->SetString(msg);
    }
}