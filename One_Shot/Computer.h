#pragma once
#include "Scene.h"

class Computer :public Scene
{
public:

    
	Computer();
	~Computer() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void Exit() override;
};

