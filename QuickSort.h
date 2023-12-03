#pragma once
#include "UFO.h"
// Follows the example shown in Lecture Notes for Module 6 - Sorting: Quick Sort
// "https://www.onlinegdb.com/ryRlgsGgD"

// currently works to sort by date

void swap(UFOsighting *a, UFOsighting *b) {
    UFOsighting t = *a;
    *a = *b;
    *b = t;
}

// Function to partition the sightings on the basis of pivot element
int partition(vector<UFOsighting> &sightings, int low, int high) {
    // Select the pivot element
    int pivot = sightings.at(low).date;
    int up = low, down = high;

    while(up < down)
    {
        for (int j = up; j < high; j++)
        {
            if(sightings.at(up).date > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--)
        {
            if(sightings.at(down).date < pivot)
                break;
            down--;
        }
        if (up < down)
            swap(&sightings.at(up), &sightings.at(down));
    }
    swap(&sightings.at(low), &sightings.at(down));
    return down;
}

void quickSort(vector<UFOsighting> &sightings, int low, int high) {
    if (low < high) // low = 0, high = sightings.size() - 1
    {
        int pivot = partition(sightings, low, high);
        quickSort(sightings, low, pivot - 1);
        quickSort(sightings, pivot + 1, high);
    }
}