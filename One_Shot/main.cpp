#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "TileManager.h"

int main()
{
    //FRAMEWORK.Init(640 , 480, "One shot!"); 원본 크기
    FRAMEWORK.Init(960, 720, "One Shot");
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tile Loader Example");

    TileManager tileMgr;
    if (!tileMgr.Load("resources/red_start.png", "resources/tile_objects_red_start.csv")) {
        return -1;
    }

    sf::Sprite wall = tileMgr.GetSprite("Red Wall Tile");
    sf::Sprite bed = tileMgr.GetSprite("Bed (Pillow + Blanket)");

    wall.setPosition(100, 100);
    bed.setPosition(140, 100);

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();
        }

        window.clear();
        window.draw(wall);
        window.draw(bed);
        window.display();
    }
    return 0;
}