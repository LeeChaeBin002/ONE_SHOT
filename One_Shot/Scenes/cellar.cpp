#include "stdafx.h"
#include "cellar.h"
#include "livingRoom.h"
#include "GameState.h"

cellar::cellar():Scene(SceneIds::cellar)
{
   
}
void cellar::Init()
{
    soundIds.push_back("Audio/BGM/SomeplaceIKnow.ogg");
    texIds.push_back("graphics/Tilesets/dark_stairs.png");
    texIds.push_back("graphics/Characters/niko.png");
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");

    if (!ANI_CLIP_MGR.Exists("idleNico")) 
    {
        ANI_CLIP_MGR.Load("animations/idleNico.csv");
    }

    if (!TEXTURE_MGR.Load("graphics/Tilesets/dark_stairs.png"))
    {
        std::cerr << "Cellar 배경 텍스처 로드 실패" << std::endl;
    }
    cellarBg = new SpriteGo("graphics/Tilesets/dark_stairs.png", "CellarBg");
    
    Utils::SetOrigin(cellarBg->GetSprite(), Origins::TL);
    
    auto windowSize = FRAMEWORK.GetWindowSizeF();
    cellarBg->SetPosition({ windowSize.x * 0.5f, windowSize.y * 0.5f });
    
    AddGameObject(cellarBg);

    TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
    go->SetString("cellar");
    go->SetCharacterSize(30);
    go->SetFillColor(sf::Color::White);
    //go->SetOrigin(Origins::TL); // 추가
    go->SetPosition({ 20.f, 0.f }); // 추가, 여백
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

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
    player->SetPosition(center);

    player->SetSpeed(150.f);
    player->Reset();
    AddGameObject(player);

    Scene::Init();
}
void cellar::Enter()
{
    Scene::Enter();

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center({ 335.f, 235.f });
    if (player && player->GetState() == PlayerState::HoldingBulb)
    player->SetPosition(center);
    player->ApplyStateTexture();
    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");

    positionSet = false;

    if (GameState::playerState == PlayerState::HoldingBulb)
    {
        std::string brightBgPath = "graphics/Tilesets/light_stairs.png";
        if (!TEXTURE_MGR.Load(brightBgPath))
        {
            std::cerr << "밝은 계단 배경 텍스처 로드 실패" << std::endl;
        }
        else
        {
            cellarBg->GetSprite().setTexture(TEXTURE_MGR.Get(brightBgPath));
            std::cout << "전구 들고 있음 → 지하실 밝은 배경 적용" << std::endl;
        }
    }
    
}
void cellar::Update(float dt)
{
    //if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    //{
    //    SCENE_MGR.ChangeScene(SceneIds::LivingRoom);  // ESC 누르면 거실로 돌아감
    //}
    if (worldView.getSize().x == 0 || worldView.getSize().y == 0)
    {
        return;
    }
    // 마우스 위치를 world 좌표로 변환
    player->Update(dt);
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
    if (playerPos.x >= 330 && playerPos.x <= 350 &&
        playerPos.y >= 230 && playerPos.y <= 250)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::LivingRoom);
        }
    }
    //지하실문 열기
    if (playerPos.x >= 850 && playerPos.x <= 930 &&
        playerPos.y >= 740 && playerPos.y <= 780)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::cellar2);
        }
    }

    if (!positionSet)
    {
        if (SCENE_MGR.GetPreviousScene() == SceneIds::LivingRoom)
        {
            // 거실에서 온경우
            player->SetPosition({ 335.f, 235.f });
        }
        if (SCENE_MGR.GetPreviousScene() == SceneIds::cellar2)
        {
            // 지하실2에서 온경우
            player->SetPosition({ 870.f, 750.f });
        }
        
        positionSet = true;



    }

}
void cellar::Draw(sf::RenderWindow& window)
{
    window.setView(worldView);
    Scene::Draw(window);  // Scene 내부에 player 그리는지 확인
   
    window.setView(uiView);
}
void cellar::Release()
{

}
void cellar::screenchange(const std::string& msg)
{

}
void cellar::Exit()
{
    bgm.stop(); // 음악 정지
    positionSet = false;
    Scene::Exit();
}
