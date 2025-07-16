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
        std::cerr << "Cellar ��� �ؽ�ó �ε� ����" << std::endl;
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
    //go->SetOrigin(Origins::TL); // �߰�
    go->SetPosition({ 20.f, 0.f }); // �߰�, ����
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
            std::cerr << "���� ��� ��� �ؽ�ó �ε� ����" << std::endl;
        }
        else
        {
            cellarBg->GetSprite().setTexture(TEXTURE_MGR.Get(brightBgPath));
            std::cout << "���� ��� ���� �� ���Ͻ� ���� ��� ����" << std::endl;
        }
    }
    
}
void cellar::Update(float dt)
{
    //if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    //{
    //    SCENE_MGR.ChangeScene(SceneIds::LivingRoom);  // ESC ������ �ŽǷ� ���ư�
    //}
    if (worldView.getSize().x == 0 || worldView.getSize().y == 0)
    {
        return;
    }
    // ���콺 ��ġ�� world ��ǥ�� ��ȯ
    player->Update(dt);
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(FRAMEWORK.GetWindow());
    sf::Vector2f mouseWorldPos = FRAMEWORK.GetWindow().mapPixelToCoords(mousePixelPos, worldView);
    if (!player) return;

    // ���� ��ǥ�� ���ڿ��� ǥ��
    std::ostringstream oss;
    oss << "Mouse World Pos: (" << mouseWorldPos.x << ", " << mouseWorldPos.y << ")";
    messageText->SetString(oss.str());

    // ����: �÷��̾� ���� worldView �̵�
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
    //���Ͻǹ� ����
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
            // �Žǿ��� �°��
            player->SetPosition({ 335.f, 235.f });
        }
        if (SCENE_MGR.GetPreviousScene() == SceneIds::cellar2)
        {
            // ���Ͻ�2���� �°��
            player->SetPosition({ 870.f, 750.f });
        }
        
        positionSet = true;



    }

}
void cellar::Draw(sf::RenderWindow& window)
{
    window.setView(worldView);
    Scene::Draw(window);  // Scene ���ο� player �׸����� Ȯ��
   
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
    bgm.stop(); // ���� ����
    positionSet = false;
    Scene::Exit();
}
