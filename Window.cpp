//
// Created by Anna Sicoli on 11/28/23.
//

#include "Window.h"
#include "Toolbox.h"
#include "Screen.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include <iostream>
#include <vector>

// checks the length of a string so that it does not extend past the edge of the borders of the right pane
string lengthCheck(string base) {
    int size = base.size();
    if (size > 19) {
        base.erase(16, base.size() - 16);
        base += "...";
    }
    return base;
}

// generates the sighting data that appears on the right side
string sightingsString(vector<UFOsighting> &sightings, const int &page_num) {
    string str;
    for (int i = page_num; i < sightings.size(); i++) {
        if (i == page_num + 6) { // maximum UFO data to display
            break;
        }
        if (sightings.at(i).date == -1) {
            str = "No UFOs Sighted";
            break;
        }
        //converts YYYYMMDD which is how it is stored to sort it to MM/DD/YYYY to print it
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
    //to get all of the things stored in the toolbox

    //I put the sprites in here because they might need to be edited
    sf::Sprite mapSprite(toolbox.mapTexture); //create the sprite for the map

    //sets the sprites and position for all of the windows
    sf::Sprite window1(toolbox.window1);
    window1.setPosition(20, 20);

    sf::Sprite window2(toolbox.window2);
    window2.setPosition(730, 20);
    sf::Text cursorPosition;

    sf::Sprite window3(toolbox.window3);
    window3.setPosition(20, 500);

    //this draws the text that says where the cursor is clicking
    cursorPosition.setFont(toolbox.font);
    cursorPosition.setCharacterSize(13);
    cursorPosition.setFillColor(sf::Color::Green);
    cursorPosition.setPosition(745, 110);

    //this is used for heat map mode. This prints the directions for using heat map mode
    sf::Text time;
    time.setFont(toolbox.font);
    time.setCharacterSize(18);
    time.setFillColor(sf::Color::Green);
    time.setPosition(745, 110);
    time.setString ("Click on the map to see \n"
                    "all the UFOs at a date. \n"
                    "The first date is \n"
                    "01/01/1969 and the most \n"
                    "recent is 12/22/2022 \n");

    //sets up the text for printing how fast quick sort is
    sf::Text quickText;
    quickText.setFont(toolbox.font);
    quickText.setCharacterSize(21);
    quickText.setFillColor(sf::Color::Green);
    quickText.setStyle(sf::Text::Bold);
    quickText.setPosition(35, 538);

    //sets up the text for printing how fast merge sort is
    sf::Text mergeText;
    mergeText.setFont(toolbox.font);
    mergeText.setCharacterSize(21);
    mergeText.setFillColor(toolbox.green);
    mergeText.setFillColor(sf::Color::Green);
    mergeText.setStyle(sf::Text::Bold);
    mergeText.setPosition(35, 565);

    // created by Aidan 12:47 12/3
    sf::Text sightingData; // displayed on right when user clicks the map

    sightingData.setFont(toolbox.font);
    sightingData.setCharacterSize(13);
    sightingData.setFillColor(toolbox.green);
    sightingData.setFillColor(sf::Color::Green);
    sightingData.setPosition(745, 135);
    sightingData.setStyle(sf::Text::Bold);

    //Neon green rectangle. This is what the use clicks on to toggle the heat map timeline
    //This is especially important in getting the x value, needed for toggling the tiimeline
    sf::RectangleShape timeline(sf::Vector2f(620, 10));
    timeline.setPosition(35, 450);
    timeline.setFillColor(sf::Color::Green);

    Screen screen;
    std::vector <std::vector <float>> locations = {{-128, 25}, {-127, 26}, {-90, 30}};
    //these are the borders

    vector<UFOsighting> sightings, sightings2;
    int longitude;
    int latitude;
    int page_num = 0; // increment/decrement this num by 6 as the user pages up and down to see the UFO data

    while (toolbox.window.isOpen()) { //starts window
        sf::Event event;

        while (toolbox.window.pollEvent(event)) { //while the window isn't closed
            if (event.type == sf::Event::Closed)
                toolbox.window.close();

            sf::Vector2i position = sf::Mouse::getPosition(toolbox.window); //gets mouse pos relative to window

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//on left click
                //left click basically makes it a scroll bar
                //this makes sure the cursor is in the bounds of the timeline
                if (position.x > timeline.getPosition().x
                    and position.x < timeline.getPosition().x + timeline.getSize().x
                    and position.y > timeline.getPosition().y
                    and position.y < timeline.getPosition().y + timeline.getSize().y
                    and toolbox.toggleLines == false) {

                    toolbox.circles.clear(); //clears last click's circles
                    toolbox.timePos = position.x; //moves the button
                    toolbox.timeButton->onClick(); //function to change the circles
                    toolbox.timeButton->getSprite()->setPosition(position.x - toolbox.timeButtonTexture.getSize().x/2, 440);
                    //prints how fast each sort is
                    mergeText.setString ("Merge sort: " + to_string(toolbox.merge_all) + " ms");
                    quickText.setString ("Quick sort: " + to_string(toolbox.quick_all) + " ms");
                }
            }

            //Edited by Anna on 12/3 at 5:43 PM
            if (event.type == sf::Event::MouseButtonPressed) {//on mouse click for upButton
                if (position.x > toolbox.upButton->getPosition().x
                    and position.x < toolbox.upButton->getPosition().x + toolbox.upButtonTexture.getSize().x
                    and position.y > toolbox.upButton->getPosition().y
                    and position.y < toolbox.upButton->getPosition().y + toolbox.upButtonTexture.getSize().y) {
                    //makes sure the click is in the bounds of the up button
                    toolbox.upButton->onClick();
                    page_num -= 6; //scrolls through pages
                    if (page_num < 0) {
                        page_num += 6;
                    }
                    sightingData.setString(sightingsString(sightings, page_num));
                }
                if (position.x > toolbox.downButton->getPosition().x
                    and position.x < toolbox.downButton->getPosition().x + toolbox.downButtonTexture.getSize().x
                    and position.y > toolbox.downButton->getPosition().y
                    and position.y < toolbox.downButton->getPosition().y + toolbox.downButtonTexture.getSize().y) { //down button
                    //makes sure the click is in the bounds of the downbutton
                    toolbox.downButton->onClick();
                    page_num += 6; //scrolls through pages
                    if (page_num > sightings.size() - 1) {
                        page_num -= 6;
                    }
                    sightingData.setString(sightingsString(sightings, page_num));
                }
                //this clicks on the reset button to clear the timeline and map
                if (position.x > toolbox.xButton->getPosition().x
                    and position.x < toolbox.xButton->getPosition().x + toolbox.xButtonTexture.getSize().x
                    and position.y > toolbox.xButton->getPosition().y
                    and position.y < toolbox.xButton->getPosition().y + toolbox.xButtonTexture.getSize().y) {
                    toolbox.xButton->onClick();
                    //makes sure click is in bounds of the xbutton
                    //clears info about the latest cursor click off the screen
                    screen.updateLines(-1,-1);
                    cursorPosition.setString("");
                    sightingData.setString("");
                    time.setString("");
                    toolbox.timeButton->getSprite()->setPosition(35, 440); //resets it to the initial position at the beginning of the timeline
                }
                if ((position.x > screen.xpos) and (position.x < screen.usaMap.getSize().x + screen.xpos) and
                    (position.y > screen.ypos) and (position.y < screen.usaMap.getSize().y + screen.ypos) and
                    toolbox.toggleTimeline == false) {
                    //checks if the click is on the map
                    toolbox.toggleLines = true; //this is important so that the line and heat map don't show up at the same time
                    time.setString(""); //this clears the directions for the heatmap off of the screen

                    //this draws the mouse click
                    cursorPosition.setStyle(sf::Text::Bold);
                    cursorPosition.setString("(" + std::to_string(screen.getLongitude(position.x - screen.xpos)) + ", " +
                                             std::to_string(screen.getLatitude(position.y - screen.ypos)) + ")");
                    //prints coordinate that was clicked on the map in terms of latiude and longitude
                    std::string str = cursorPosition.getString();
                    screen.updateLines(position.x, position.y); //moves the red lines to be at the click on the map

                    // Edited by Aidan 12:12 PM 12/3
                    page_num = 0;
                    longitude = static_cast<int>(screen.getLongitude(position.x - screen.xpos));
                    latitude = static_cast<int>(screen.getLatitude(position.y - screen.ypos));

                    // positions of latitude and longitude are swapped in GetSigthingsAt method
                    sightings = toolbox.List.GetSightingsAt(latitude, longitude).second;
                    sightings2 = sightings;

                    // sort sightings with quick sort and merge sort
                    // compare times of each algortihm

                    //Edited by Carter 9:41 PM 12/3
                    auto start_quick = chrono::high_resolution_clock ::now();
                    quickSort(sightings, 0, sightings.size() - 1);
                    auto end_quick = std::chrono::high_resolution_clock::now();

                    auto start_merge = chrono::high_resolution_clock ::now();
                    mergeSort(sightings2, 0, sightings2.size() - 1);
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
            }
        }

        screen.usaMap.display();
        toolbox.window.clear();

        //displays the windows
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

        world.setPosition(screen.xpos, screen.ypos); //this is slightly different because it is a render texture. It has to be a render texture so you can draw the lines
        toolbox.window.draw(world);

        //draw text (which is sometimes "" depending on the click and toggle statuses)
        toolbox.window.draw(cursorPosition);
        toolbox.window.draw(mergeText);
        toolbox.window.draw(quickText);
        toolbox.window.draw(sightingData);
        toolbox.window.draw(time);

        //this draws all the circles, but only if toggleTimeline is true
        //draws all the circles for the heatmap timeline
        if (toolbox.toggleTimeline == true) {
            for (int i = 0; i < toolbox.circles.size(); i++) {
                toolbox.window.draw(toolbox.circles[i].second);
            }
        }

        toolbox.window.display();
    }
}

void increasePage(){ //function for upButton
    Toolbox& toolbox = toolbox.getInstance();
    toolbox.page++;
}

void decreasePage(){ //function for downButton
    Toolbox& toolbox = toolbox.getInstance();
    toolbox.page--;
}

void timeScroll(){ //function for timeline scroll button
    Toolbox &toolbox = toolbox.getInstance();
    toolbox.toggleTimeline = true;
    // toolbox.timePos is where x is stored since this function can't have parameters
    // Repeat sorting process for a list of all sightings to display timeline of sighting events
    // Again, comparing time for quicksort and mergesort to complete using std::chrono

    //Editted by Carter 3:07 PM 12/4
    vector<UFOsighting> all_sightings, all_sightings2;
    all_sightings = toolbox.List.GetAllSightings();
    all_sightings2 = toolbox.List.GetAllSightings();

    auto start_quick_all = chrono::high_resolution_clock ::now();
    quickSort(all_sightings, 0, all_sightings.size() - 1);
    auto end_quick_all = std::chrono::high_resolution_clock::now();

    auto start_merge_all = chrono::high_resolution_clock ::now();
    mergeSort(all_sightings2, 0, all_sightings2.size() - 1);
    auto end_merge_all = std::chrono::high_resolution_clock::now();

    auto quick_time = end_quick_all - start_quick_all; // calc time elapsed
    auto merge_time = end_merge_all - start_merge_all;

    toolbox.quick_all = std::chrono::duration_cast<chrono::milliseconds >(quick_time).count();
    toolbox.merge_all = std::chrono::duration_cast<chrono::milliseconds>(merge_time).count();

    // We will create and populate a vector with the UFOsightings to be displayed at a given point on the slider
    // Slider increments by 5 pixels for a total of 620 pixels giving us 124 possibile positions
    // We know that the position of the Slider from the screen is offset by 35 pixels
    // Thus, we can determine a number of ufos to display per position
    // And, we can use this to display this number of UFOs (a block from the starting index to the starting index + the num to display
    // As well, we can determine which position the cursor is in and change the starting index accordingly based on the num to display
    vector<UFOsighting> sightings_within_date_range;
    unsigned int num_ufos_display_per_5_pixels = all_sightings.size()/124;
    unsigned int display_window_index = (toolbox.timePos - 35) / 5;
    for (unsigned int ufo_event = display_window_index; ufo_event < display_window_index + num_ufos_display_per_5_pixels; ufo_event++) {
        if (ufo_event < all_sightings.size()) {
            sightings_within_date_range.push_back(all_sightings[ufo_event]);
        }
    }

    for (auto& sighting : sightings_within_date_range) {
        //inverse longitude and latitude formula
        int map_offset_x = 45;
        int map_offset_y = 70;
        int map_width_x = 650;
        int map_width_y = 362;
        int longitude_range = 63;
        int latitude_range = 31;

        //converts latitude and longitude to x and y pos relative to the map
        int x_position = (sighting.coordinate.second + 128) * (double)(map_width_x / longitude_range) + map_offset_x;
        int y_position = (54 - sighting.coordinate.first) * (double)(map_width_y / latitude_range) + map_offset_y;

        int circle_radius = 2;
        for (int i = 0; i < toolbox.circles.size(); i++) {
            if (toolbox.circles[i].second.getPosition().x == x_position
            and toolbox.circles[i].second.getPosition().y == y_position) {
                circle_radius += 2;
            }
        }
        sf::CircleShape circle(circle_radius);
        circle.setPosition(x_position,y_position);
        circle.setFillColor(sf::Color::White);

        toolbox.circles.push_back({circle_radius, circle});
    }

}
void reset(){ //function for xButton
    Toolbox& toolbox = toolbox.getInstance();
    toolbox.toggleTimeline = false;
    toolbox.toggleLines = false;

}
