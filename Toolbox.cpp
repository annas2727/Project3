//
// Created by Anna Sicoli on 11/28/23.
//

#include "Toolbox.h"

Toolbox::Toolbox() {
    window.create(sf::VideoMode(1030, 700), "I Want to Believe");
    font.loadFromFile("files/Courier New Regular.ttf"); //loads font
    mapTexture.loadFromFile("files/usaMap.jpg"); //loads map image
    window1.loadFromFile("files/window1.jpg");
    window2.loadFromFile("files/window2.jpg");
    redLineH.loadFromFile("files/redLineH.jpg");
    redLineV.loadFromFile("files/redLineV.jpg");
    upButton.loadFromFile("files/upButton.jpg");
    downButton.loadFromFile("files/downButton.jpg");

    sf::Color green(0x02ff0); //neon green color that's used in the window
    sf::CircleShape circle(50);
    circle.setFillColor(green);
    //create initial window
}

