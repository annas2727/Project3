//
// Created by Anna Sicoli on 11/28/23.
//

#include "Window.h"
#include "Toolbox.h"
#include "Screen.h"
#include <iostream>
#include <vector>

void startWindow(UFOlist& ufolist) {

    Toolbox &toolbox = Toolbox::getInstance();

    //I put the sprites in here because they might need to be edited
    sf::Sprite mapSprite(toolbox.mapTexture); //create the sprite for the map

    sf::Sprite window1(toolbox.window1);
    window1.setPosition(20, 20);

    sf::Sprite window2(toolbox.window2);
    window2.setPosition(730, 20);
    sf::Text cursorPosition;

    cursorPosition.setFont(toolbox.font);
    cursorPosition.setCharacterSize(16);
    cursorPosition.setFillColor(toolbox.green);
    cursorPosition.setFillColor(sf::Color::Green);
    cursorPosition.setPosition(745, 60);

    Screen screen;
    std::vector <std::vector <float>> locations = {{-128, 25}, {-127, 26}, {-90, 30}};
    while (toolbox.window.isOpen()) {
        sf::Event event;

        while (toolbox.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                toolbox.window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//on left click

                //also add bounds to make it inside the world window
                sf::Vector2i position = sf::Mouse::getPosition(
                        toolbox.window); //gets position of cursor relative to window
                if ((position.x > screen.xpos) and (position.x < screen.usaMap.getSize().x + screen.xpos) and
                    (position.y > screen.ypos) and (position.y < screen.usaMap.getSize().y + screen.ypos)) {

                    //cursorPosition.setString("(" + std::to_string(position.x) + ", " + std::to_string(position.y));

                    //this draws the mouse click
                    cursorPosition.setStyle(sf::Text::Bold);
                    cursorPosition.setString("(" + std::to_string(screen.getLongitude(position.x - screen.xpos)) + ", " +
                    std::to_string(screen.getLatitude(position.y - screen.ypos)) + ")");

                    std::string str = cursorPosition.getString();
                    screen.updateLines(position.x, position.y);

                }
                //this is going to have to find and print all the surrounding UFOs
                // SELECT count(*) FROM nuforc_reports where city_longitude is not null and country = "USA"
            }
        }
        // -180 to 180
        // -90 to 90

        screen.usaMap.display();
        toolbox.window.clear();


        toolbox.window.draw(mapSprite);
        toolbox.window.draw(window1);
        toolbox.window.draw(window2);


        sf::Sprite world(screen.usaMap.getTexture()); //have to convert renderTexture back into sprite
        world.setPosition(screen.xpos, screen.ypos);
        toolbox.window.draw(world);

        toolbox.window.draw(cursorPosition);

        toolbox.window.display();
    }
}
