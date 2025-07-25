#include "stdafx.h"
#include "Computer.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "Room.h"
#include "SceneMgr.h"

Computer::Computer() :Scene(SceneIds::Computer)
{

}
void Computer::Init()
{
    passwordText = new TextGo("fonts/TerminusTTF-Bold.ttf");
    passwordText->Init();
    passwordText->SetString("PassWord: ");
    passwordText->SetCharacterSize(30);
    passwordText->SetFillColor(sf::Color::White);
    passwordText->SetPosition({ 150.f, 350.f });
    passwordText->sortingLayer = SortingLayers::UI;
    passwordText->sortingOrder = 1;
    AddGameObject(passwordText);

    texIds.push_back("graphics/Pictures/cg_desktop_no_effects.png");
    fontIds.push_back("fonts/TerminusTTF-Bold.ttf");
    // 컴퓨터 화면 이미지 추가
    SpriteGo* computerScreen = new SpriteGo("graphics/Pictures/cg_desktop_no_effects.png", "ComputerScreen");
   
    const sf::Texture* texture = computerScreen->GetSprite().getTexture();
    //sf::Vector2f center = FRAMEWORK.GetWindowSizeF() * 0.5f;

    if (texture != nullptr)
    {
        sf::Vector2u textureSize = texture->getSize();     // 이미지 원본 크기
        
        std::cout << "Original Texture Size: " << textureSize.x << ", " << textureSize.y << std::endl;
        // 640x480 크기로 스케일링
        float scaleX = 640.0f / textureSize.x;
        float scaleY = 480.0f / textureSize.y;

        computerScreen->SetScale({ scaleX, scaleY });
    }
    else
    {
        std::cerr << "컴퓨터 스크린 텍스처 로드 실패!" << std::endl;
    }
    computerScreen->SetOrigin(Origins::TL);
    computerScreen->SetPosition({ 0.f, 0.f });
    AddGameObject(computerScreen);
    
}
void Computer::Enter()
{
    Scene::Enter();
    SOUNDBUFFER_MGR.Load("Audio/SE/pc_messagebox.wav");
    bgm.setBuffer(SOUNDBUFFER_MGR.Get("Audio/SE/pc_messagebox.wav"));
    bgm.setLoop(false);
    bgm.play();

    auto size = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
    for (auto obj : gameObjects)
    {
        if (obj->GetName() == "ComputerScreen")
        {
            SpriteGo* screen = dynamic_cast<SpriteGo*>(obj);
            if (screen)
            {
                const sf::Texture* texture = screen->GetSprite().getTexture();
                if (texture)
                {
                    sf::Vector2u textureSize = texture->getSize();
                    float scaleX = size.x / static_cast<float>(textureSize.x);
                    float scaleY = size.y / static_cast<float>(textureSize.y);

                    screen->SetScale({ scaleX, scaleY });
                    screen->SetOrigin(Origins::TL);
                    screen->SetPosition({ 0.f, 0.f });
                }
            }
        }
    }
    uiView.setSize(size);
    uiView.setCenter(center);
    worldView.setSize(size);
    worldView.setCenter(center);



    std::cout << "Computer UI Scene Entered" << std::endl;
}
void Computer::Update(float dt)
{

    // 1~9 숫자키 입력 체크
    for (int num = 1; num <= 9; ++num)
    {
        if (InputMgr::GetKeyDown(static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + num - 1)))
        {
            if (passwordInput.size() < passwordLength)
            {
                passwordInput += std::to_string(num);
               
                passwordText->SetString("PassWord: " + passwordInput);

                if (passwordInput.size() == passwordLength)
                {


                    // TODO: 비밀번호 확인 로직
                    if (passwordInput == "2817")  // 예시: 정답
                    {
                        std::cout << "비밀번호 정답!" << std::endl;
                        ShowMessage("Password Success!");
                        SOUNDBUFFER_MGR.Load("Audio/SE/door_open.wav");
                        bgm.setBuffer(SOUNDBUFFER_MGR.Get("Audio/SE/door_open.wav"));
                        bgm.setLoop(false);
                        bgm.play();

                        Scene* scene = SCENE_MGR.GetScene(SceneIds::Room);
                        Room* room = dynamic_cast<Room*>(scene);
                        if (room)
                        {
                            room->SetAccessLivingRoom(true);
                        }
                    }
                    else
                    {
                        std::cout << "비밀번호 틀림!" << std::endl;
                        ShowMessage("Password Failed!");
                        
                    }

                    passwordInput.clear();  // 다시 입력받기
                  
                }
            }
        }


        if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
        {
            SCENE_MGR.ChangeScene(SceneIds::Room);  // ESC 누르면 방으로 돌아감
        }
    }
        Scene::Update(dt);
}

void Computer::Draw(sf::RenderWindow& window)
{
    Scene::Draw(window);

}
void Computer::Exit()
{
    Scene::Exit();
    std::cout << "Computer UI Scene Exited" << std::endl;
}

void Computer::Release()
{
    bgm.stop();
}
void Computer::ShowMessage(const std::string& msg)
{
    if (passwordText)
    {
        passwordText->SetString(msg);
    }
}


