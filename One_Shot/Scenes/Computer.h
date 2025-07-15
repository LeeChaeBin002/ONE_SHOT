#pragma once
#include "Scene.h"

class Computer :public Scene
{
protected:
    std::string passwordInput;     // 입력한 비밀번호
    const int passwordLength = 4;  // 비밀번호 길이 제한
    TextGo* passwordText = nullptr; // 입력 표시할 텍스트
    sf::Sound bgm;
   
    
public:

    
	Computer();
	~Computer() override = default;

    void Init() override;
    void Enter() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    void Release() override;
    void Exit() override;
    void ShowMessage(const std::string& msg);
    

};

