//
// Created by avk on 13.12.15.
//

#include "FenwickTree.h"
#include <cmath>
#include <iostream>
#include <limits.h>

using namespace std;

//#define min(a,b) ((a) < (b) ? (a) : (b))

FenwickTree:: FenwickTree(vector<vector<int>> data) : data(data) {
    prepare();
}

void FenwickTree::prepare() {
    // Initializing left and right
    redRed.resize(data.size(), vector<int>(data[0].size(), INT_MAX));
    greenGreen.resize(data.size(), vector<int>(data[0].size(), INT_MAX));
    redGreen.resize(data.size(), vector<int>(data[0].size(), INT_MAX));
    greenRed.resize(data.size(), vector<int>(data[0].size(), INT_MAX));

    updateGreenGreen();
    updateGreenRen();
    updateRedGreen();
    updateRedRed();
}

void FenwickTree::updateRedRed() {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            int min = INT_MAX;
            for (int k = i - lastBit(i); k < data.size(); ++k)
                for (int l = j - lastBit(j); l < data[i].size(); ++l)
                    if (data[i][j] < min)
                        min = data[i][j];
            redRed[i][j] = min;
        }
    }
}

void FenwickTree::updateRedGreen() {
    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            int min = INT_MAX;
            for (int k = i - lastBit(i); k < data.size(); ++k) {

            }
        }
    }
}


int FenwickTree::getMin(int leftIndex, int rightIndex, int upIndex, int downIndex) {
    int i = upIndex, j = leftIndex;
    int result = INT_MAX;

    for(; i + lastBit(i) <= downIndex; i += lastBit(i)) {
        for(; j + lastBit(j) <= rightIndex; j += lastBit(j)) {
            result = min(result, right[i][j]);
        }
    }

    result = min(result, data[i-1][j-1]);
    i = downIndex, j = rightIndex;

    for(; i - lastBit(i) >= upIndex; i -= lastBit(i))
        for(; j - lastBit(j) >= leftIndex; j -= lastBit(j))
            result = min(result, left[i][j]);

    return result;
}

void FenwickTree::print() {

    std::cout << "printing data" << endl;
    for(const auto it: data) {
        for(const auto jt : it) {
            cout << jt << " ";
        }
        cout << endl;
    }
}

