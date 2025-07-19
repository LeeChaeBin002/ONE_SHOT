#pragma once
#include "GameObject.h"
#include "SpriteGo.h"
class Storage :
    public GameObject
{
protected:
    sf::Sprite inventorybg;
    int selectedIndex = -1;//0���ͽ����̿��� �������Ƚ�
    int currentSlotIndex = 0;
    int selectedSlotIndex = 0;
    float highlightTime = 0.f;
    float highlightSpeed = 3.f;
    bool initialized = false;
  
public:
   
    std::vector<bool> slotHasItem;
    std::vector<bool> slotHasOverlay;
    std::function<void(int)> onItemSelected;
    std::function<void()> onRemoveSelectedIcon;

    std::vector<std::string> slotItemPaths;
    std::vector<SpriteGo*> slots;
    std::string texId;
    std::string GetItemIconPath(int index) const;
    static Storage& Instance();
    bool IsInitialized() const { return initialized; }
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
    void ClearItems();
    int GetCurrentSlotIndex() const;
};

