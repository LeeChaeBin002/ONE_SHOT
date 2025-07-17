#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
class Storage :
    public GameObject
{
protected:
    sf::Sprite inventorybg;


public:

    std::string texId;
    Storage(const std::string name = "");
    ~Storage() override = default;
    void Init() override;

    void Release() override;

    void Reset() override;

    void Update(float dt) override;

    void Draw(sf::RenderWindow& window) override;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

};

