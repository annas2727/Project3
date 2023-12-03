#include "Window.h"
#include "UFO.h"
#include "Quicksort.h"
#include "MergeSort.h"
#include "Toolbox.h"
#include "Screen.h"
#include <iostream>
#include <vector>

int main() {
    // Lazy way to source the file

    UFOlist List("files/Project3/cmake-build-debug\\UFOPROJECTCSV.csv");
    /*
    // check to see if sorts work
    vector<UFOsighting> og_list = List.GetSightingsAt(40, -90).second; // test nums
    for (const auto& sight : og_list) {
        cout << sight.date << " ";
    }
    cout << "\n";
    quickSort(og_list, 0, og_list.size() - 1); // can be swapped with merge sort
    for (const auto& sight : og_list) {
        cout << sight.date << " ";
    }
    */

    /*
     // Checks every grid tile
    int w = 0;
    for (int j = 23; j <= 54; j++) {
        for (int i = -128; i <= -65; i++) {
            // for each UFO sighting within grid tile
            for (const auto& sighting : List.GetSightingsAt(j, i).second) {
                // if valid sighting
                if (List.GetSightingsAt(j, i).first)
                    cout << ++w << '\n';
                // << " " << sighting.coordinate.first << " ," << sighting.coordinate.second << " , " << sighting.date << ", " << sighting.shape << " , " << sighting.duration << endl;
            }
        }
    }
    */
    startWindow(List);
}
