#include "stdafx.h"
#include "cellar.h"

cellar::cellar():Scene(SceneIds::cellar)
{
   
}
void cellar::Init()
{

}
void cellar::Enter()
{
    if (InputMgr::GetKeyDown(sf::Keyboard::BackSpace))
    {
        SCENE_MGR.ChangeScene(SceneIds::LivingRoom);  // ESC 누르면 거실로 돌아감
    }
}
void cellar::Update(float dt)
{

}
void cellar::Draw(sf::RenderWindow& window)
{

}
void cellar::Release()
{

}
void cellar::screenchange(const std::string& msg)
{

}
void cellar::Exit()
{

}
