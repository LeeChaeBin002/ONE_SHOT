#pragma once
#include "Scene.h"
#include "Room.h"
#include "TextGo.h"
#include "SpriteGo.h"

class Storage;
class Room :
    public Scene
{
protected:
    int instructionIndex = 0;         // 현재 instruction 이미지 인덱스
    bool isShowingInstruction = true; // instruction을 보여주는 중인지
    std::vector<SpriteGo*> instructions;

    AniPlayer* player = nullptr;
    sf::Sound bgm;
	Storage* storage;
    sf::Sprite background;
    bool positionSet = false;
    bool hasRemote = false;
    bool ShowedWindowMsg = false;
  
    TextGo* messageText = nullptr;
    bool canAccessLivingRoom = false;
    sf::Sound instructionEffect;

public:
    Room();
    ~Room() override = default;

    void SetAccessLivingRoom(bool access) { canAccessLivingRoom = access; }
    bool CanAccessLivingRoom() const { return canAccessLivingRoom; }
    void CheckItempickup();
    void ShowMessage(const std::string& msg);
    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window)override;
    void Release() override;
    void screenchange(const std::string& msg);
    void Exit()override;

};

