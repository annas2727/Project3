#include "UFO.h"
// UFOread Helper
ufo_grid UFOlist::GridInitializer() {
    ufo_grid init;
    // 1D initial
    vector<UFOsighting> UFO_tmp;
    // 2D initial
    vector<vector<UFOsighting>> X_tmp;
    // Initial values (impossible)
    pair<double, double> init_coordinate = {-1000, -1000};
    int init_date = -1;
    string init_str;
    // Initial UFO
    UFOsighting initU(init_coordinate, init_date, init_str, init_str);
    // Size of Actual Map in Latitude & Longitude
    int height = 54-23;
    int width = (-65) - (-128);
    // Initialize 1D
    UFO_tmp.push_back(initU);
    // Initialize 2D
    for (int x = 0; x <= width; x++) {
        X_tmp.push_back(UFO_tmp);
    } // 3D ufo grid is fully initialized
    for (int y = 0; y <= height; y++) {
        init.push_back(X_tmp);
    }
    return init;
}
// UFOlist Constructor Helper
ufo_grid UFOlist::UFOread(string file) {
    ufo_grid init = GridInitializer();
    // Open csv data
    fstream fin;
    fin.open(file, ios::in);
    // Temp storage
    vector<string> row;
    string line, data;
    // While we can still read
    getline(fin, line);
    // Checks for EOF
    while (getline(fin, line)) {
        // Clear vector for use
        row.clear();
        // Stream breaks up cells
        stringstream s(line);
        // While there are cells to be read
        while (getline(s, data, ','))
            row.push_back(data);
        // Format cell data
        double y = stod(row[0]);
        double x = stod(row[1]);
        pair coordinate{y, x};
        // Formats data
        int date = stoi(row[2].substr(0, 4)
                        + row[2].substr(5, 2) + row[2].substr(8, 2));

        string shape = row[3];
        string duration = row[4];
        // Instantiate UFO sighting
        UFOsighting U(coordinate, date, shape, duration);
        // Normalize latitude and longitude values
        int y_index = int(y - 23);
        int x_index = int(x + 128);
        int height = 54-23;
        int width = (-65) - (-128);
        // Checks for good input excluding title row
        if (y_index >= 0 and y_index <= height and x_index >= 0 and x_index <= width) {
            // If this grid square is yet to be populated
            if (init[y_index][x_index][0].date == -1) {
                // Clear placeholder initial sighting
                init[y_index][x_index].clear();
                // Instantiate real sighting
                init[y_index][x_index].push_back(U);
            }
            else {
                // Instantiate at back of vector for grid square
                init[y_index][x_index].push_back(U);
            }
        }
    }
    return init;
}

UFOlist::UFOlist(string file) {
    UFOs = UFOread(file);
}
// Get ufo list
ufo_grid UFOlist::GetGrid() {
    return UFOs;
}
// Get grid square from list
pair<bool, vector<UFOsighting>> UFOlist::GetSightingsAt(double y, double x) {
   // Normalize Values
   int y_index = int(y - 23);
   int x_index = int(x + 128);
   // Bool determines if it holds any real sighting data, or just placeholder initial values
   bool containsUFO = true;
    // If placeholder
   if (UFOs[y_index][x_index][0].date == -1)
       containsUFO = false;

   return {containsUFO, UFOs[y_index][x_index]};
}


