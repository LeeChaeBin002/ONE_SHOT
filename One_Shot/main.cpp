#include "stdafx.h"

int main()
{
    //FRAMEWORK.Init(640 , 480, "One shot!"); ���� ũ��
    FRAMEWORK.Init(960, 720, "One Shot");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}