//
// Created by Anna Sicoli on 11/28/23.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Button.h"
#include "UFO.h"

class Toolbox {
    Toolbox();
public:
    ~Toolbox() {};
    sf::RenderWindow window;

    UFOlist List = UFOlist("files/UFOPROJECTCSV.csv");

    sf::Texture window1;
    sf::Texture window2;
    sf::Texture window3;
    sf::Texture mapTexture;
    sf::Texture redLineV;
    sf::Texture redLineH;
    sf::Texture upButtonTexture;
    sf::Texture downButtonTexture;
    sf::Texture timeButtonTexture;
    sf::Texture xButtonTexture;

    sf::Font font;
    sf::Color green;
    sf::CircleShape circle;
    Button* upButton;
    Button* downButton;
    Button* timeButton;
    Button* xButton;

    int page = 0;

    static Toolbox &getInstance() //ensures that there is only one window
    {
        static Toolbox toolbox;
        return toolbox;
    }
};


