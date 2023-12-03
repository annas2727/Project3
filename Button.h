//
// Created by Anna Sicoli on 12/3/2023.
//

#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
#include "Window.h"

//implements each widget
// SFML application window /

class Button{
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;
    std::function<void(void)> function; //onclick function
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    /*Constructs a new object at the specified _position which invokes
     * the _onClick callback when clicked.  */
    ~Button(); //destructor
    sf::Vector2f getPosition();
    /*Returns the position of the button.  */
    sf::Sprite* getSprite();
    //Returns the current sprite of the button.
    void setSprite(sf::Sprite* _sprite);
    //Sets this button’s visualization to the specified _sprite.
    void onClick();
    //Invokes the button’s callback method (usually called when clicked).
};