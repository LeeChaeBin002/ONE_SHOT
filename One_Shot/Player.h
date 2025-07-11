#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
protected:
    sf::Sprite body;
    std::string TexId = "graphics/niko.png";

   
public:
    Player(const std::string& name = "");
    ~Player()override = default;
};

