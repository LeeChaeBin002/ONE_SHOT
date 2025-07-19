#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
class Storage :
    public GameObject
{
protected:
    sf::Sprite inventorybg;
    int selectedIndex = -1;//0부터시작이여서 전숫자픽스
    int currentSlotIndex = 0;
    int selectedSlotIndex = 0;
    float highlightTime = 0.f;
    float highlightSpeed = 3.f;
    
  
public:
    std::vector<bool> slotHasItem;
    std::vector<bool> slotHasOverlay;
    std::function<void(int)> onItemSelected;
    std::vector<SpriteGo*> slots;
    std::string texId;
    static Storage& Instance();

    Storage(const std::string name = "Storage");
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
    void AddItem(const std::string& texPath);
    void TriggerSelect();
};

