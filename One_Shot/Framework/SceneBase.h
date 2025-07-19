#pragma once
#include "Scene.h"
#include "SpriteGo.h"
class SceneBase :
    public Scene
{
protected:
    SpriteGo* selectedIcon = nullptr;

    void HandleItemSelected(int index);
    void RemoveSelectedIcon();

public:
    SceneBase(SceneIds id); 
    virtual ~SceneBase()=default;
    virtual void Draw(sf::RenderWindow& window) override;


};

