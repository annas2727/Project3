//
// Created by Anna Sicoli on 11/28/23.
//

#include "Screen.h"
#include "Toolbox.h"
#include <iostream>

Screen::Screen(){
    Toolbox& toolbox = Toolbox::getInstance();
    sf::Sprite map(toolbox.mapTexture);
    usaMap.create(toolbox.mapTexture.getSize().x, toolbox.mapTexture.getSize().y);
    //gets size of image and sets the render texture to that

    usaMap.draw(map);
}

void Screen::updateLines(int x, int y) {
    Toolbox& toolbox = Toolbox::getInstance();
    sf::Sprite map(toolbox.mapTexture);

    sf::Sprite redLineH(toolbox.redLineH);
    redLineH.setPosition(0,y - ypos);
    //subtract from map placement to make coordinates in terms of (0,0);

    sf::Sprite redLineV(toolbox.redLineV);
    redLineV.setPosition(x - xpos,0);

    usaMap.draw(map);
    usaMap.draw(redLineH);
    usaMap.draw(redLineV);
}

float Screen::getLongitude(int x) { //x is the pos the user clicks
    //continental us is -128 to -65 (align the lines)
    float scaleFactor = (128 - 65) / (double)usaMap.getSize().x; //longitude width / pixels
    return (double) scaleFactor * x - 128;
}

float Screen::getLatitude(int y) { //y is the pos the user clicks
    //continental us is 23 to 52
    float scaleFactor = (54 - 23) / (double)usaMap.getSize().y; //latitude width / pixels
    return 54 - (double)scaleFactor * y;
}