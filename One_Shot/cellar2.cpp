#include "stdafx.h"
#include "cellar2.h"
#include "SpriteGo.h"

cellar2::cellar2():Scene(SceneIds::cellar2)
{
}
void cellar2::Init()
{
    soundIds.push_back("Audio/BGM/SomeplaceIKnow.ogg");
    texIds.push_back("graphics/Tilesets/dark_stairs2.png");
    texIds.push_back("graphics/Characters/niko.png");
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");
    if (!ANI_CLIP_MGR.Exists("idleNico"))
    {
        ANI_CLIP_MGR.Load("animations/idleNico.csv");
    }

    if (!TEXTURE_MGR.Load("graphics/Tilesets/dark_stairs2.png"))
    {
        std::cerr << "Cellar 배경 텍스처 로드 실패" << std::endl;
    }
    SpriteGo* cellar2Bg = new SpriteGo("graphics/Tilesets/dark_stairs2.png", "Cellar2Bg");
    Utils::SetOrigin(cellar2Bg->GetSprite(), Origins::MC);

    auto windowSize = FRAMEWORK.GetWindowSizeF();
    cellar2Bg->SetPosition({ windowSize.x * 0.5f, windowSize.y * 0.5f });
    AddGameObject(cellar2Bg);

    TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
    go->SetString("cellar2");
    go->SetCharacterSize(30);
    go->SetFillColor(sf::Color::White);
    go->SetPosition({ 20.f, 0.f });
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
void cellar2::Enter()
{
    Scene::Enter();

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center({ 335.f, 235.f });//수정

    player->SetPosition(center);
    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");

    positionSet = false;

}
void cellar2::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    {
        SCENE_MGR.ChangeScene(SceneIds::cellar);  // ESC 누르면 지하실1로 돌아감
    }
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
    //지하실문 열기
    if (playerPos.x >= 350 && playerPos.x <= 400 &&
        playerPos.y >= 440 && playerPos.y <= 480)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::cellar);
        }
    }

    if (!positionSet)
    {
        if (SCENE_MGR.GetPreviousScene() == SceneIds::cellar)
        {
            // 지하실에서 온경우
            player->SetPosition({ 348.f, 460.f });
        }

        positionSet = true;



    }
}
void cellar2::Draw(sf::RenderWindow& window)
{
    window.setView(worldView);
    Scene::Draw(window);  // Scene 내부에 player 그리는지 확인

    window.setView(uiView);
}
void cellar2::Release()
{

}
void cellar2::Exit()
{
    bgm.stop(); // 음악 정지
    positionSet = false;
    Scene::Exit();
}