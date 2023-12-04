#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Sighting class holds individual sighting data
struct UFOsighting {
    pair<double, double> coordinate; // (Y, X)
    int date; // YYYYMMDD
    string shape, duration;
    // Constructor
    UFOsighting(pair<double, double>& coordinate_, int& date_, string& shape_, string& duration_) :
                coordinate(coordinate_), date(date_), shape(shape_), duration(duration_) {}
};
// typedef 3D vector of UFO sightings to store vector of UFO sightings at a given X, Y
typedef vector<vector<vector<UFOsighting>>> ufo_grid;

// UFOlist class manages sightings en masse
class UFOlist {
    // Initializes ufo grid
    ufo_grid GridInitializer();
    // Populates ufo grid
    pair<ufo_grid, vector<UFOsighting>> UFOread(string file);
    // Container for CSV information
    ufo_grid UFOs;
    // Container for all info sightings in a single vector
    vector<UFOsighting> all_sightings;
public:
    UFOlist(string file);

    ufo_grid GetGrid();
    vector<UFOsighting> GetAllSightings();

    // First -> bool to check if grid is populated (don't want to display initializer values)
    // Second-> Gets vector of sighting given an exact X, Y
    pair<bool, vector<UFOsighting>> GetSightingsAt(double y, double x); // latitude then longitude
};
