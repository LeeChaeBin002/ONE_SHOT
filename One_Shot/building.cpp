#include "stdafx.h"
#include "building.h"
#include "SpriteGo.h"

building::building():Scene(SceneIds::building)
{

}
void building::Init()
{
    soundIds.push_back("Audio/BGM/SomeplaceIKnow.ogg");
    texIds.push_back("graphics/Tilesets/in_blue.png");
    texIds.push_back("graphics/Characters/niko.png");
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");

    if (!ANI_CLIP_MGR.Exists("idleNico")) // ���� Ȯ�� �� �ε�
    {
        ANI_CLIP_MGR.Load("animations/idleNico.csv");
    }

    if (!TEXTURE_MGR.Load("graphics/Tilesets/in_blue.png"))
    {
        std::cerr << "LivingRoom 배경 텍스처 로드 실패" << std::endl;
    }

    SpriteGo* buildingBg = new SpriteGo("graphics/Tilesets/in_blue.png", "buildingBg");
    buildingBg->SetPosition({ -30.f, -45.f });
    AddGameObject(buildingBg);

    TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
    go->SetString("building");
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
void building::Enter()
{
    Scene::Enter();

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    //MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");
    player->ApplyStateTexture();
    positionSet = false;
}
void building::Update(float dt) 
{
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

    //밖으로 나가기(수정)
    if (playerPos.x >= 530 && playerPos.x <= 590 &&
        playerPos.y >= 150 && playerPos.y <= 200)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::Stage1);
        }
    }

    if (!positionSet)
    {
        if (SCENE_MGR.GetPreviousScene() == SceneIds::cellar)
        {
            // 밖에서 온 경우
            player->SetPosition({ /* 지하실 문 앞 좌표 예시 */ 720.f, 250.f });
        }
        else
        {
            // 안에서 온 경우
            player->SetPosition({ 308.f, 180.f });
        }
        positionSet = true;



    }

    //if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    //{
    //    SCENE_MGR.ChangeScene(SceneIds::Room);  // 예시: 방으로 돌아가기
    //}
    Scene::Update(dt);

}
void building::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window); // Scene이 알아서 worldView, uiView, gameObjects draw

    if (messageText && messageText->GetActive())
    {
        messageText->Draw(window);
    }
}
void building::Release()
{

}
void building::ShowMessage(const std::string& msg)
{
    if (messageText)
    {
        messageText->SetString(msg);
    }

}
void building::Exit()
{
    bgm.stop(); // 음악 정지
    positionSet = false;
    Scene::Exit(); // 부모 클래스 Exit 호출 (리소스 언로드 등)


}