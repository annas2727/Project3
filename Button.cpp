//
// Created by Anna Sicoli on 12/3/2023.
//

#include "Button.h"
#include "Toolbox.h"

//implements each widget

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick){ //second param
    function = _onClick;
    position = _position;
} //button constructor

sf::Vector2f Button::getPosition() {
    return position;
}
sf::Sprite* Button::getSprite(){ //returns sprite
    return &sprite;
}
void Button::setSprite(sf::Sprite* _sprite){ //sets sprite
    sprite = *_sprite;
}
//Sets this button’s visualization to the specified _sprite.
void Button::onClick(){
    function();
}
//Invokes the button’s callback method (usually called when clicked).
