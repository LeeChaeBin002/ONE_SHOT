#include "stdafx.h"

int main()
{
    //FRAMEWORK.Init(640 , 480, "One shot!"); 원본 크기
    FRAMEWORK.Init(960, 720, "One Shot");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}