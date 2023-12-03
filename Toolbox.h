//
// Created by Anna Sicoli on 11/28/23.
//

#include <SFML/Graphics.hpp>
#include "Screen.h"
#pragma once

class Toolbox {
    Toolbox();
public:
    ~Toolbox() {};
    sf::RenderWindow window;

    sf::Texture window1;
    sf::Texture window2;
    sf::Texture mapTexture;
    sf::Texture redLineV;
    sf::Texture redLineH;
    sf::Texture upButton;
    sf::Texture downButton;
    //Screen worldMap;

    sf::Font font;
    sf::Color green;
    sf::CircleShape circle;


    static Toolbox &getInstance() //ensures that there is only one window
    {
        static Toolbox toolbox;
        return toolbox;
    }
};


