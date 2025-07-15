#pragma once
#include "Scene.h"

class Computer :public Scene
{
protected:
    std::string passwordInput;     // �Է��� ��й�ȣ
    const int passwordLength = 4;  // ��й�ȣ ���� ����
    TextGo* passwordText = nullptr; // �Է� ǥ���� �ؽ�Ʈ
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

