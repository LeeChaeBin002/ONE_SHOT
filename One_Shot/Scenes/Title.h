#pragma once
#include "Scene.h"
#include "Framework/TextGo.h"
class Title :
    public Scene
{
protected:
    sf::Sprite spritetitle;
    sf::Sprite spriteMode;
    TextGo* screen;
    TextGo* clickStart;
    SceneIds changeScene = SceneIds::Mode;
public:
    Title() :Scene(SceneIds::Title){}
    ~Title() override = default;

    void screenchange(const std::string& msg);
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window);

};

