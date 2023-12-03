#pragma once
#include "UFO.h"
// Follows the example shown in Lecture Notes for Module 6 - Sorting: Merge Sort
// "https://www.onlinegdb.com/HJT6FfMlv"

// currently works to sort by date

// Merge two subarrays from sightings
void merge(vector<UFOsighting> &sightings, int left, int mid, int right) {
    // Create X & Y
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<UFOsighting> X;
    vector<UFOsighting> Y;

    for (int i = 0; i < n1; i++)
        X.push_back(sightings.at(left + i)); // populate X and Y to the point of n1 and n2 respectively
    for (int j = 0; j < n2; j++)
        Y.push_back(sightings.at(mid + 1 + j));

    // Merge the arrays X and Y into sightings
    int i, j, k;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (X.at(i).date <= Y.at(j).date) // make comparison based on dates
        {
            sightings.at(k) = X.at(i);
            i++;
        }
        else
        {
            sightings.at(k) = Y.at(j);
            j++;
        }
        k++;
    }
    // When we run out of elements in either X or Y append the remaining elements
    while (i < n1)
    {
        sightings.at(k) = X.at(i);
        i++;
        k++;
    }

    while (j < n2)
    {
        sightings.at(k) = Y.at(j);
        j++;
        k++;
    }
}


void mergeSort(vector<UFOsighting> &sightings, int left, int right) {
    // left = 0, right = sightings.size() - 1
    if (left < right)
    {
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;

        mergeSort(sightings, left, mid);
        mergeSort(sightings, mid + 1, right);

        // Merge the sorted subarrays
        merge(sightings, left, mid, right);
    }
}
