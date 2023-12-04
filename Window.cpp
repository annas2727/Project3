//
// Created by Anna Sicoli on 11/28/23.
//

#include "Window.h"
#include "Toolbox.h"
#include "Screen.h"
#include <iostream>
#include <vector>
#include "QuickSort.h"
#include "MergeSort.h"

// checks the length of a string so that it does not extend past the edge of the borders
string lengthCheck(string base) {
    int size = base.size();
    if (size > 19) {
        base.erase(16, base.size() - 16);
        base += "...";
    }
    return base;
}

// generates the data that appears on the right side
string sightingsString(vector<UFOsighting> &sightings, const int &page_num) {
    string str;
    for (int i = page_num; i < sightings.size(); i++) {
        if (i == page_num + 6) { // maximum UFO data to display
            break;
        }
        if (sightings.at(i).date == -1) {
            str = "No UFO's Sighted";
            break;
        }
        string date = to_string(sightings.at(i).date);
        string year = date.substr(0, 4);
        string month = date.substr(4, 2);
        string day = date.substr(6, 2);
        str += month;
        str += "/";
        str += day;
        str += "/";
        str += year;
        str += "\nDuration: ";
        str += lengthCheck(sightings.at(i).duration);
        str += "\nShape: ";
        str += lengthCheck(sightings.at(i).shape);
        str += "\n\n";
    }
    return str;
}


void startWindow() {

    Toolbox &toolbox = Toolbox::getInstance();

    //I put the sprites in here because they might need to be edited
    sf::Sprite mapSprite(toolbox.mapTexture); //create the sprite for the map

    sf::Sprite window1(toolbox.window1);
    window1.setPosition(20, 20);

    sf::Sprite window2(toolbox.window2);
    window2.setPosition(730, 20);
    sf::Text cursorPosition;

    sf::Sprite window3(toolbox.window3);
    window3.setPosition(20, 500);

    cursorPosition.setFont(toolbox.font);
    cursorPosition.setCharacterSize(13);
    cursorPosition.setFillColor(toolbox.green);
    cursorPosition.setFillColor(sf::Color::Green);
    cursorPosition.setPosition(745, 110);

    sf::Text quickText;
    quickText.setFont(toolbox.font);
    quickText.setCharacterSize(21);
    quickText.setFillColor(toolbox.green);
    quickText.setFillColor(sf::Color::Green);
    quickText.setStyle(sf::Text::Bold);
    quickText.setPosition(35, 538);

    sf::Text mergeText;
    mergeText.setFont(toolbox.font);
    mergeText.setCharacterSize(21);
    mergeText.setFillColor(toolbox.green);
    mergeText.setFillColor(sf::Color::Green);
    mergeText.setStyle(sf::Text::Bold);
    mergeText.setPosition(35, 565);

    // created by Aidan 12:47 12/3
    sf::Text sightingData;

    sightingData.setFont(toolbox.font);
    sightingData.setCharacterSize(13);
    sightingData.setFillColor(toolbox.green);
    sightingData.setFillColor(sf::Color::Green);
    sightingData.setPosition(745, 135);
    sightingData.setStyle(sf::Text::Bold);

    sf::RectangleShape timeline(sf::Vector2f(620, 10));
    timeline.setPosition(35, 450);
    timeline.setFillColor(sf::Color::Green);

Screen screen;
    std::vector <std::vector <float>> locations = {{-128, 25}, {-127, 26}, {-90, 30}};

    vector<UFOsighting> sightings, sightings2;
    int longitude;
    int latitude;
    int page_num = 0; // increment/decrement this num by 6 as the user pages up and down to see the UFO data

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

                    // Edited by Aidan 12:12 PM 12/3
                    page_num = 0;
                    longitude = static_cast<int>(screen.getLongitude(position.x - screen.xpos));
                    latitude = static_cast<int>(screen.getLatitude(position.y - screen.ypos));

                    // positions of latitude and longitude are swapped in GetSigthingsAt method
                    // get sightings
                    sightings = toolbox.List.GetSightingsAt(latitude, longitude).second;
                    sightings2 = sightings;

                    // sort sightings with quick sort and merge sort
                    // compare times of each algortihm

                    //Edited by Carter 9:41 PM 12/3
                    auto start_quick = chrono::high_resolution_clock ::now();
                    quickSort(sightings, 0, sightings.size() - 1);
                    auto end_quick = std::chrono::high_resolution_clock::now();

                    auto start_merge = chrono::high_resolution_clock ::now();
                    mergeSort(sightings2, 0, sightings.size() - 1);
                    auto end_merge = std::chrono::high_resolution_clock::now();

                    auto quick_time = end_quick - start_quick; // calc time elapsed
                    auto merge_time = end_merge - start_merge;
                    // this is the time taken in nanoseconds for both sorting algorithms
                    long long  ns_quick = std::chrono::duration_cast<chrono::nanoseconds>(quick_time).count();
                    long long  ns_merge = std::chrono::duration_cast<chrono::nanoseconds>(merge_time).count();

                    //adds the time it takes for quick sort vs merge sort to complete
                    quickText.setString ("Quick Sort: " + to_string(ns_quick) + " ns");
                    mergeText.setString("Merge Sort: " + to_string(ns_merge) + " ns");

                    sightingData.setString(sightingsString(sightings, page_num));
                }

                //this is going to have to find and print all the surrounding UFOs
                // SELECT count(*) FROM nuforc_reports where city_longitude is not null and country = "USA"
            }

            //Edited by Anna on 12/3 at 5:43 PM
            if (event.type == sf::Event::MouseButtonPressed) {//on mouse click for upButton
                sf::Vector2i position = sf::Mouse::getPosition(toolbox.window); //gets mouse pos relative to window
                if (position.x > toolbox.upButton->getPosition().x
                    and position.x < toolbox.upButton->getPosition().x + toolbox.upButtonTexture.getSize().x
                    and position.y > toolbox.upButton->getPosition().y
                    and position.y < toolbox.upButton->getPosition().y + toolbox.upButtonTexture.getSize().y) {
                    toolbox.upButton->onClick();
                    page_num -= 6;
                    if (page_num < 0) {
                        page_num += 6;
                    }
                    sightingData.setString(sightingsString(sightings, page_num));
                }
                if (position.x > toolbox.downButton->getPosition().x
                    and position.x < toolbox.downButton->getPosition().x + toolbox.downButtonTexture.getSize().x
                    and position.y > toolbox.downButton->getPosition().y
                    and position.y < toolbox.downButton->getPosition().y + toolbox.downButtonTexture.getSize().y) { //down button
                    toolbox.downButton->onClick();
                    page_num += 6;
                    if (page_num > sightings.size() - 1) {
                        page_num -= 6;
                    }
                    sightingData.setString(sightingsString(sightings, page_num));
                }
                if (position.x > toolbox.timeButton->getPosition().x
                    and position.x < toolbox.timeButton->getPosition().x + toolbox.timeButtonTexture.getSize().x
                    and position.y > toolbox.timeButton->getPosition().y
                    and position.y < toolbox.timeButton->getPosition().y + toolbox.timeButtonTexture.getSize().y) {
                    toolbox.timeButton->onClick();

                }
            }
        }

        screen.usaMap.display();
        toolbox.window.clear();

        toolbox.window.draw(window1);
        toolbox.window.draw(window2);
        toolbox.window.draw(window3);

        toolbox.window.draw(timeline);

        //draw buttons

        toolbox.window.draw(*(toolbox.upButton->getSprite()));
        toolbox.window.draw(*(toolbox.downButton->getSprite()));
        toolbox.window.draw(*(toolbox.timeButton->getSprite()));
        toolbox.window.draw(*(toolbox.xButton->getSprite()));

        sf::Sprite world(screen.usaMap.getTexture()); //have to convert renderTexture back into sprite
        world.setPosition(screen.xpos, screen.ypos);
        toolbox.window.draw(world);

        toolbox.window.draw(cursorPosition);
        toolbox.window.draw(mergeText);
        toolbox.window.draw(quickText);
        toolbox.window.draw(sightingData);

        toolbox.window.display();
    }
}

void increasePage(){ //returns position
    Toolbox& toolbox = toolbox.getInstance();
    toolbox.page++;
}

void decreasePage(){ //returns position
    Toolbox& toolbox = toolbox.getInstance();
    toolbox.page--;
}

void timeScroll() { /*UFOlist& ufolist*/
    Toolbox &toolbox = toolbox.getInstance();
    ufo_grid all_sightings = toolbox.List.GetGrid();
    for (auto &row: all_sightings) {
        for (auto &sightings_at_location: row) {
            for (auto &sighting: sightings_at_location) {

                // IF DATE = (GET DATE FROM CLICK WITHIN RECTANGLE)
                // RECTANGLE (X -> 620)
                // ufo_grid
                return;
            }
        }
    }
}
void exit() {
}