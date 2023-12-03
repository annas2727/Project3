//
// Created by Anna Sicoli on 11/28/23.
//
#include <SFML/Graphics.hpp>
#pragma once

class Screen {
public:
    Screen();
    void updateLines(int x, int y);
    int xpos = 25; // this is where the map is placed
    int ypos = 55;

    sf::RenderTexture usaMap;
    float getLongitude(int x);
    float getLatitude(int y);
    bool isWithinRadius (float x, float y);
    std::vector <std::vector <float>> locationsWithinRadius (std::vector <std::vector <float>>); //change to a map or whatever data structure
};