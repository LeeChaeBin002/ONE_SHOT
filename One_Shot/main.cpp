#include "stdafx.h"

int main()
{
    //FRAMEWORK.Init(640 , 480, "One shot!"); ���� ũ��
     //FRAMEWORK.Init(960 , 720, "One shot!");1.5�� ũ��
    FRAMEWORK.Init(640, 480, "One Shot");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}