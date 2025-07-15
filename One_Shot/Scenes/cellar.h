#pragma once
#include "Scene.h"
class cellar : public Scene
{
protected:

public:
	cellar();
	~cellar()override=default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window)override;
    void Release() override;
    void screenchange(const std::string& msg);
    void Exit()override;

};

