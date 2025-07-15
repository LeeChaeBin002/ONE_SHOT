#include "stdafx.h"
#include "Framework.h"
#include <iostream>
#include <windows.h>
#include <filesystem>

void Framework::Init(int w, int h, const std::string& t)
{ 
    // 현재 실행 파일의 경로 출력
    char path[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, path);
    std::cout << "Current Working Directory: " << path << std::endl;
	window.create(sf::VideoMode(w, h), t);
    texIds = {
        "graphics/Characters/niko.png",
  
    };

    fontIds = {
        "fonts/TerminusTTF-Bold.ttf"
    };
    soundIds = {
        
    };

	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

    for (const auto& id : fontIds)
    {
        if (!FONT_MGR.Exists(id))
        {
           
           FONT_MGR.Load("fonts/TerminusTTF-Bold.ttf");    
        }
    }

    Utils::Init();
	InputMgr::Init();
    SOUND_MGR.Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
   

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        time += deltaTime;
        realTime = realDeltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            InputMgr::UpdateEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            // 마우스 이동 이벤트 감지

            if (event.type == sf::Event::MouseMoved)
            {
                const sf::View& view = SCENE_MGR.GetCurrentWorldView();
                if (view.getSize().x == 0.f || view.getSize().y == 0.f)
                {
                    std::cerr << "Warning: worldView not initialized yet.\n";
                    continue; // worldView 초기화 안 됐으면 skip
                }
                // 월드 좌표 변환
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos,view);


                std::cout << "Mouse World Position: (" << static_cast<int>(mouseWorldPos.x) << ", " << static_cast<int>(mouseWorldPos.y) << ")" << std::endl;
            }
        }

        InputMgr::Update(deltaTime);

        // Update
        SOUND_MGR.Update(deltaTime);

#ifdef DEF_DEV
        if (InputMgr::GetKeyDown(sf::Keyboard::F10))
        {
            Variables::isDrawHitBox = !Variables::isDrawHitBox;
        }
#endif


        SCENE_MGR.Update(deltaTime);

        // Draw
        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SOUND_MGR.Release();
	SCENE_MGR.Release();

	SOUNDBUFFER_MGR.Unload(soundIds);
	FONT_MGR.Unload(fontIds);
	TEXTURE_MGR.Unload(texIds);
}
