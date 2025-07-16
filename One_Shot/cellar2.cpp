#include "stdafx.h"
#include "cellar2.h"
#include "SpriteGo.h"
#include "Framework.h"



cellar2::cellar2():Scene(SceneIds::cellar2)
{
}

void cellar2::Init()
{
    InitAnimation();
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
        std::cerr << "Cellar ��� �ؽ�ó �ε� ����" << std::endl;
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
    sf::Vector2f center({ 348.f, 460.f });//����

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
        SCENE_MGR.ChangeScene(SceneIds::cellar);  // ESC ������ ���Ͻ�1�� ���ư�
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
    //std::cout << "worldView center: " << worldView.getCenter().x << ", " << worldView.getCenter().y << std::endl;

    //���Ͻǹ� ����
    if (playerPos.x >= 350 && playerPos.x <= 400 &&
        playerPos.y >= 440 && playerPos.y <= 480)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {

            SCENE_MGR.ChangeScene(SceneIds::cellar);
        }
    }
    if (playerPos.x >= 1060 && playerPos.x <= 1080 &&
        playerPos.y >= 440 && playerPos.y <= 480)
    {
        if (InputMgr::GetKeyDown(sf::Keyboard::Z))
        {
          
            PlayAnimation();
        }
        
    }

    if (!positionSet)
    {
        if (SCENE_MGR.GetPreviousScene() == SceneIds::cellar)
        {
            // ���Ͻǿ��� �°��
            player->SetPosition({ 348.f, 460.f });
        }
        positionSet = true;


        if (!isPlaying) return;
    }

    if (isPlaying)
    {
      
        frameTime += dt;
        if (frameTime >= frameDuration)
        {
            frameTime = 0.f;
            currentFrame++;
            if (currentFrame >= textures.size())
            {
                isPlaying = false; // ������ �ߴ�
                currentFrame = textures.size() - 1; // ������ ������ ����
            
                sprite.setTexture(*textures[currentFrame]);
                UpdateSpritePosition();
            }
          
            
                sprite.setTexture(*textures[currentFrame]);
                // �ٽ� ������ �� ��ġ ����
                sf::Vector2u texSize = textures[currentFrame]->getSize();
                sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

                float scaleX = windowSize.x / texSize.x;
                float scaleY = windowSize.y / texSize.y;
                float scale = std::max(scaleX, scaleY);
                sprite.setScale(scale, scale);

                sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
                sprite.setPosition(windowSize.x / 2.f+offsetX, windowSize.y / 2.f+offsetY);
        }

    }
       
}
void cellar2::Draw(sf::RenderWindow& window)
{
    window.setView(worldView);
    Scene::Draw(window);
    window.setView(uiView);  // UI �信�� �׸���
    if (isPlaying && !textures.empty())
    {
        window.draw(sprite);
    }

  
}
void cellar2::Release()
{

}
void cellar2::Exit()
{
    bgm.stop(); // ���� ����
    positionSet = false;
    Scene::Exit();
}
void cellar2::InitAnimation()
{
    
    for (int i = 0; i < 10; ++i)
    {
        std::string path = "graphics/Pictures/b" + std::to_string(i) + ".png";

        if (!TEXTURE_MGR.Load(path))
        {
            std::cerr << "Failed to load " << path << std::endl;
            continue;
        }

        sf::Texture* texture = &TEXTURE_MGR.Get(path);
        if (texture == nullptr)
        {
            std::cerr << "Failed to get texture: " << path << std::endl;
            continue;
        }

        textures.push_back(texture);
    }

    if (!textures.empty())
    {
        sprite.setTexture(*textures[0]);
        Utils::SetOrigin(sprite, Origins::MC);
    }

}
void cellar2::PlayAnimation()
{

    //sprite.setPosition(worldView.getCenter());
    //std::cout << "PlayAnimation ȣ���! textures size: " << textures.size() << std::endl;
    //std::cout << "textures size: " << textures.size() << std::endl;

    if (textures.empty())
    {
        std::cerr << "PlayAnimation ȣ�� ���� InitAnimation�� ȣ���ϼ���!" << std::endl;
        return;
    }
    isPlaying = true;
    currentFrame = 0;
    frameTime = 0.f;

    sprite.setTexture(*textures[currentFrame]);
    UpdateSpritePosition();

    sf::Vector2u texSize = textures[currentFrame]->getSize();
    sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
    float scaleX = windowSize.x / texSize.x;
    float scaleY = windowSize.y / texSize.y;
    float scale = std::max(scaleX, scaleY);
    sprite.setScale(scale, scale);
    // �߾ӿ� ��ġ
    sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    sprite.setPosition(windowSize.x / 2.f + offsetX, windowSize.y / 2.f+ offsetY);
}

void cellar2::UpdateSpritePosition()
{
    sf::Vector2u texSize = textures[currentFrame]->getSize();
    sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

    float scaleX = windowSize.x / texSize.x;
    float scaleY = windowSize.y / texSize.y;
    float scale = std::max(scaleX, scaleY);
    sprite.setScale(scale, scale);

    sprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    sprite.setPosition(windowSize.x / 2.f + offsetX, windowSize.y / 2.f + offsetY);
}
