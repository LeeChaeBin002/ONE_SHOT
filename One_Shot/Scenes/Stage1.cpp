#include "stdafx.h"
#include "Stage1.h"
#include "SpriteGo.h"

Stage1::Stage1():Scene(SceneIds::Stage1), introState(IntroState::WaitingToStart),
introTimer(0.f)
{
    
}
void Stage1::Init()
{
    soundIds.push_back("Audio/BGM/SomeplaceIKnow.ogg");
    texIds.push_back("graphics/Tilesets/out_blue.png");
    texIds.push_back("graphics/Characters/niko.png");
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");

    if (!ANI_CLIP_MGR.Exists("idleNico")) // ���� Ȯ�� �� �ε�
    {
        ANI_CLIP_MGR.Load("animations/idleNico.csv");
    }

    if (!TEXTURE_MGR.Load("graphics/Tilesets/out_blue.png"))
    {
        std::cerr << "LivingRoom 배경 텍스처 로드 실패" << std::endl;
    }

    SpriteGo* Stage1Bg = new SpriteGo("graphics/Tilesets/out_blue.png", "Stage1Bg");
    Stage1Bg->SetPosition({ -510.f, -45.f });
    AddGameObject(Stage1Bg);

    TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
    go->SetString("");
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

    introImage = new SpriteGo("graphics/Pictures/intro.jpg", "IntroImage");
    introImage->SetOrigin(Origins::MC);
    introImage->SetPosition({ FRAMEWORK.GetWindowSizeF().x * 0.5f, FRAMEWORK.GetWindowSizeF().y - 750.f }); // 화면 아래 시작
    AddGameObject(introImage);

    Scene::Init();

}
void Stage1::Enter()
{
    Scene::Enter();
    MUSIC_MGR.StopBGM();

    introState = IntroState::WaitingToStart;
    introTimer = 0.f;
    introFinished = false;
   
    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    
    player->ApplyStateTexture();
    positionSet = false;
}
void Stage1::Update(float dt)
{
    const float targetY = -60.f + (introImage->GetGlobalBounds().height * 0.5f);
    switch (introState)
    {
    case IntroState::WaitingToStart:
            introTimer += dt;
            if (introTimer >= 1.f) // 2초 대기 후 시작
            {
                introState = IntroState::Playing;
                introTimer = 0.f;
            }
            break;
    case IntroState::Playing:
        if (introImage)
        {
            sf::Vector2f pos = introImage->GetPosition();

            if (pos.y < targetY)
            {
                pos.y += 120.f * dt; // 위로 이동

                // 목표 위치보다 더 넘어가지 않게 제한
                if (pos.y > targetY)
                    pos.y = targetY;
                introImage->SetPosition(pos);

            }
            else
            {
                introState = IntroState::WaitingAfterEnd;
                introTimer = 0.f;
            }
        }
        break;
    case IntroState::WaitingAfterEnd:
        introTimer += dt;
        if (introTimer >= 1.f)
        {
            introState = IntroState::Finished;
            if (introImage)
                introImage->SetActive(false);
            MUSIC_MGR.PlayBGM("Audio/BGM/Phosphor_slow.wav");
        }
        break;

    case IntroState::Finished:
        if (!player) return;
        player->Update(dt);

        // 마우스 위치를 world 좌표로 변환
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
        sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePixelPos, worldView);

        // 월드 좌표를 문자열로 표시
        std::ostringstream oss;
        oss << "Mouse World Pos: (" << mouseWorldPos.x << ", " << mouseWorldPos.y << ")";
        messageText->SetString(oss.str());

        // 예시: 플레이어 따라 worldView 이동
        sf::Vector2f playerPos = player->GetPosition();
        worldView.setCenter(playerPos);

        //밖으로 나가기(수정)
        if (playerPos.x >= 170 && playerPos.x <= 200 &&
            playerPos.y >= 150 && playerPos.y <= 200)
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
        break;
        }

    }


void Stage1::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window); // Scene이 알아서 worldView, uiView, gameObjects draw

    if (messageText && messageText->GetActive())
    {
        messageText->Draw(window);
    }
}
void Stage1::Release()
{
    if (introImage)
    {
        delete introImage;
        introImage = nullptr;
    }
}
void Stage1::ShowMessage(const std::string& msg)
{
    if (messageText)
    {
        messageText->SetString(msg);
    }

}
void Stage1::Exit()
{
    bgm.stop(); // 음악 정지
    positionSet = false;
    Scene::Exit(); 

}
void Stage1::InitAnimation()
{
    
}