#include "stdafx.h"
#include <SFML/Graphics.hpp>
int main()
{
    //FRAMEWORK.Init(640 , 480, "One shot!"); 원본 크기
     //FRAMEWORK.Init(960 , 720, "One shot!");1.5배 크기
    FRAMEWORK.Init(640, 480, "One Shot");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    
  
}