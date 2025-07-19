#include "stdafx.h"
#include "livingRoom.h"
#include "SpriteGo.h"
#include "Storage.h"

LivingRoom::LivingRoom() : Scene(SceneIds::LivingRoom)
{
}
void LivingRoom::Init()
{
    storage = &Storage::Instance();
    if (!storage->IsInitialized()) // Init이 두 번 실행 안되게
    {
        storage->Init();
        storage->SetActive(false);
        storage->Reset();
    }
    AddGameObject(storage);
    

    storage->onRemoveSelectedIcon = [this]()
        {
            RemoveSelectedIcon();
            
        };
    storage->onItemSelected = [this](int index)
        {
            if (selectedIcon != nullptr && selectedIcon->GetActive())
            {
                RemoveSelectedIcon();
            }
            std::string iconPath = storage->GetItemIconPath(index);
            if (iconPath.empty())
            {
                std::cout << "해당 슬롯에 아이템 없음 (하단 아이콘 표시 안함)" << std::endl;
                return;
            }

            if (!TEXTURE_MGR.Exists(iconPath))
            {
                TEXTURE_MGR.Load(iconPath);
            }

            SpriteGo* icon = new SpriteGo(iconPath, "RemoteIcon");
            icon->GetSprite().setTexture(TEXTURE_MGR.Get(iconPath));
            sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
            icon->SetPosition({ windowSize.x - 50.f, windowSize.y - 50.f });
            icon->SetScale({ 1.5f, 1.5f });
            icon->SetOrigin(Origins::MC);
            icon->SetActive(true);
            AddGameObject(icon);
            selectedIcon = icon;
        };
    
    
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
    player->ApplyStateTexture();
    player->SetSpeed(150.f);
    player->Reset();
    AddGameObject(player); 
    
    
    Scene::Init();
}

void LivingRoom::Enter()
{
    Scene::Enter();
    if (storage->GetCurrentSlotIndex() != 0) // 이미 아이템이 있으면 초기화
    {
        storage->ClearItems();
        for (const auto& itemPath : GameState::inventoryItems)
        {
            storage->AddItem(itemPath);
        }
    }
    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");
    player->ApplyStateTexture();
    positionSet = false;
}

void LivingRoom::Update(float dt)
{
    if(InputMgr::GetKeyDown(sf::Keyboard::S))
    {
        bool active = storage->GetActive();
        storage->SetActive(!active);
        std::cout << "Storage Active: " << !active << std::endl;
    }
    if (storage && storage->GetActive())
    {
        storage->Update(dt);
        return;
    }

    if (worldView.getSize().x == 0 || worldView.getSize().y == 0)
    {
       return;
    }
    // 마우스 위치를 world 좌표로 변환
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
    sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePixelPos, worldView);

    
    if (!player) return;


    // 월드 좌표를 문자열로 표시
    std::ostringstream oss;
    oss << "Mouse World Pos: (" << mouseWorldPos.x << ", " << mouseWorldPos.y << ")";
    messageText->SetString(oss.str());

    // 예시: 플레이어 따라 worldView 이동
    sf::Vector2f playerPos = player->GetPosition();
    worldView.setCenter(playerPos);


    //니코방으로 돌아가기
    if (playerPos.x >= 300  && playerPos.x <= 340 &&
        playerPos.y >= 180 && playerPos.y <= 200)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::Room);
        }
    }
    //지하실 내려가기
    if (playerPos.x >= 700 && playerPos.x <= 750 &&
        playerPos.y >= 200 && playerPos.y <= 300)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::cellar);
        }
    }
    //밖으로 나가기
    if (playerPos.x >= 140 && playerPos.x <= 180 &&
        playerPos.y >= 230 && playerPos.y <= 250)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::building);
        }
    }

    if (!positionSet)
    {
        if (SCENE_MGR.GetPreviousScene() == SceneIds::cellar)
        {
            // 지하실에서 올라온 경우
            player->SetPosition({ /* 지하실 문 앞 좌표 예시 */ 720.f, 250.f });
        }
        else
        {
            // 니코 방에서 온 경우
            player->SetPosition({ 308.f, 180.f });
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
   
    if (storage && storage->GetActive())
    {
        storage->Draw(window);
    }

    if (messageText && messageText->GetActive())
    {
        messageText->Draw(window);
    }

    if (selectedIcon != nullptr && selectedIcon->GetActive())
    {
        selectedIcon->Draw(window);
    }
}
    

void LivingRoom::Release()
{
    if (storage != nullptr)
    {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); )
        {
            if (*it == storage)
            {
                delete* it;
                it = gameObjects.erase(it);
            }
            else
            {
                ++it;
            }
        }
        storage = nullptr;
    }
}

void LivingRoom::ShowMessage(const std::string& msg)
{
    if (messageText)
    {
        messageText->SetString(msg);
    }
}
void LivingRoom::Exit()
{
    bgm.stop(); // 음악 정지
    positionSet = false;
    Scene::Exit(); // 부모 클래스 Exit 호출 (리소스 언로드 등)
}
void LivingRoom::RemoveSelectedIcon()
{
    if (selectedIcon)
    {
        selectedIcon->SetActive(false);
        for (auto it = gameObjects.begin(); it != gameObjects.end(); )
        {
            if (*it == selectedIcon)
            {
                delete* it;
                it = gameObjects.erase(it);
            }
            else
            {
                ++it;
            }
        }
        selectedIcon = nullptr;
    }
}