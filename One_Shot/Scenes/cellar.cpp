#include "stdafx.h"
#include "cellar.h"
#include "livingRoom.h"

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
    SpriteGo* cellarBg = new SpriteGo("graphics/Tilesets/living_room.png", "CellarBg");
    cellarBg->GetSprite().setOrigin(cellarBg->GetSprite().getLocalBounds().width * 0.5f,
    cellarBg->GetSprite().getLocalBounds().height * 0.5f);
    cellarBg->SetPosition({ 0.f, 0.f });
    AddGameObject(cellarBg);

    TextGo* go = new TextGo("fonts/TerminusTTF-Bold.ttf");
    go->SetString("cellar");
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
    player->SetSpeed(150.f);
    player->Reset();
    AddGameObject(player);

    Scene::Init();
}
void cellar::Enter()
{
    Scene::Enter();

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);

    messageText->SetString("");
    MUSIC_MGR.PlayBGM("Audio/BGM/SomeplaceIKnow.ogg");

    positionSet = false;
    
}
void cellar::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    {
        SCENE_MGR.ChangeScene(SceneIds::LivingRoom);  // ESC ������ �ŽǷ� ���ư�
    }
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

}
void cellar::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);

    if (messageText && messageText->GetActive())
    {
        messageText->Draw(window);
    }
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
