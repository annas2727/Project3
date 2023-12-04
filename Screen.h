//
// Created by Anna Sicoli on 11/28/23.
//
#include <SFML/Graphics.hpp>
#pragma once

class Screen {
public:
    Screen();
    void updateLines(int x, int y);
    int xpos = 45; // this is where the map is placed
    int ypos = 70;

    sf::RenderTexture usaMap;
    float getLongitude(int x);
    float getLatitude(int y);
};