#include "stdafx.h"
#include "livingRoom.h"

LivingRoom::LivingRoom() : Scene(SceneIds::LivingRoom)
{
}
void LivingRoom::Init()
{
    soundIds.push_back("Audio/BGM/SomeplaceIKnow.ogg");
    texIds.push_back("graphics/Tilesets/living_room.png");
    texIds.push_back("graphics/Characters/niko.png");
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");

    if (!ANI_CLIP_MGR.Exists("idleNico")) // ���� Ȯ�� �� �ε�
    {
        ANI_CLIP_MGR.Load("animations/idleNico.csv");
    }

    if (!TEXTURE_MGR.Load("graphics/Tilesets/living_room.png"))
    {
        std::cerr << "LivingRoom 배경 텍스처 로드 실패" << std::endl;
    }

    SpriteGo* LivingBg = new SpriteGo("graphics/Tilesets/living_room.png", "LivingRoomBg");
    LivingBg->SetPosition({ 0.f, 0.f });
    AddGameObject(LivingBg);
    
    TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
    go->SetString("Living Room");
    go->SetCharacterSize(30);
    go->SetFillColor(sf::Color::White);
    go->sortingLayer = SortingLayers::UI;
    go->sortingOrder = 0;
    AddGameObject(go);

    messageText = new TextGo("fonts/TerminusTTF-Bold.ttf");
    messageText->Init();
    messageText->SetCharacterSize(24);
    messageText->SetFillColor(sf::Color::White);
    messageText->SetPosition({ 50.f, 700.f });
    messageText->sortingLayer = SortingLayers::UI;
    messageText->sortingOrder = 1;
    AddGameObject(messageText);

    player = new AniPlayer("player");
    player->SetPosition({ 0.f, 0.f });
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

void LivingRoom::Update(float dt)
{
    
    if (!player) return;

    Scene::Update(dt);
    // 플레이어 위치 가져오기
    sf::Vector2f playerPos = player->GetPosition();
    // View의 중심을 플레이어 위치로 설정
    worldView.setCenter(playerPos);
    if (!positionSet)
    {
        for (auto obj : gameObjects)
        {
            if (obj->GetName() == "player")
            {
                obj->SetPosition({ 308.f, 180.f });
            }
           
        }
        positionSet = true;
    }

    if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    {
        SCENE_MGR.ChangeScene(SceneIds::Room);  // 예시: 방으로 돌아가기
    }
    Scene::Update(dt);
}

void LivingRoom::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window); // Scene이 알아서 worldView, uiView, gameObjects draw

    if (messageText && messageText->GetActive())
    {
        messageText->Draw(window);
    }
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