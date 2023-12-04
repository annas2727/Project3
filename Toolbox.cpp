 //
// Created by Anna Sicoli on 11/28/23.
//

#include "Toolbox.h"

Toolbox::Toolbox() {
    window.create(sf::VideoMode(1030, 700), "I Want to Believe");
    font.loadFromFile("files/Courier New Regular.ttf"); //loads font

    //initialize all the textures
    mapTexture.loadFromFile("files/usaMap.jpg");
    window1.loadFromFile("files/window1.jpg");
    window2.loadFromFile("files/window2.jpg");
    window3.loadFromFile("files/window3.jpg");
    redLineH.loadFromFile("files/redLineH.jpg");
    redLineV.loadFromFile("files/redLineV.jpg");
    upButtonTexture.loadFromFile("files/upButton.jpg");
    downButtonTexture.loadFromFile("files/downButton.jpg");
    timeButtonTexture.loadFromFile("files/timeButton.jpg");
    xButtonTexture.loadFromFile("files/xButton.jpg");

    sf::Color green(0x02ff0); //neon green color that's used in the window
    sf::CircleShape circle(50);
    circle.setFillColor(green);
    //create initial window

    sf::Sprite sprite;
    sprite.setTexture(upButtonTexture);
    //730, 20 are window2 positions
    upButton = new Button(sf::Vector2f(730 + window2.getSize().x/2 - upButtonTexture.getSize().x/2, 70), increasePage); // Resets / starts new game
    upButton->setSprite(&sprite); //sets sprite
    upButton->getSprite()->setPosition(upButton->getPosition());

    sprite.setTexture(downButtonTexture);
    downButton = new Button(sf::Vector2f(730 + window2.getSize().x/2 - downButtonTexture.getSize().x/2, 500), decreasePage); // Resets / starts new game
    downButton->setSprite(&sprite); //sets sprite
    downButton->getSprite()->setPosition(downButton->getPosition());

    sf::Sprite timeSprite;
    timeSprite.setTexture(timeButtonTexture);
    timeButton = new Button(sf::Vector2f(35, 440), increasePage); // Resets / starts new game
    timeButton->setSprite(&timeSprite);
    timeButton->getSprite()->setPosition(timeButton->getPosition());

    sf::Sprite xSprite;
    xSprite.setTexture(xButtonTexture);
    xButton = new Button(sf::Vector2f(665, 440), decreasePage); // Resets / starts new game
    xButton->setSprite(&xSprite);
    xButton->getSprite()->setPosition(xButton->getPosition());
}
