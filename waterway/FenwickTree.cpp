//
// Created by avk on 13.12.15.
//

#include "FenwickTree.h"
#include <cmath>

using namespace std;

#define max(a,b) ((a) > (b) ? (a) : (b))

FenwickTree:: FenwickTree(vector<vector<int>> data) : data(data) {
    // Setting k -> min power of 2, which bigger than data.size : (pow(2,k) >= data.size)
    for(verticalPower = 0; pow(2, verticalPower) < data.size(); ++verticalPower);
    for(horizontalPower = 0; pow(2, horizontalPower) < data[0].size(); ++horizontalPower);
    // Initializing vectors
    for(int i = 0; i <= pow(2, verticalPower); ++i) {
        left.push_back(vector<int>());
        right.push_back(vector<int>());
        for(int j = 0; j <= pow(2, horizontalPower); ++j) {
            left[i].push_back(-1);
            right[i].push_back(-1);
        }
    }
    prepare();
}

void FenwickTree::prepare() {
    for(int i = 0; i < data.size(); ++i) {
        for(int j = 0; j < data[0].size(); ++j) {
            update(i + 1, j + 1, data[i][j]);
        }
    }
}

void FenwickTree::update(int indexI, int indexJ, int value) {
    for(int i = indexI; i <= pow(2, verticalPower); i += G(i)) {
        for(int j = indexJ; j <= pow(2, horizontalPower); j += G(j)) {
            left[i][j] = max(left[i][j], value);
        }
    }

    for(int i = indexI; i > 0; i -= G(i)) {
        for(int j = indexJ; j > 0; j -= G(i)) {
            right[i][j] = max(right[i][j], value);
        }
    }
}

int FenwickTree::getMax(int leftIndex, int rightIndex, int upIndex, int downIndex) {
    int i = leftIndex, j = upIndex;
    int result = 0;

    for(; i + G(i) <= rightIndex; i += G(i)) {
        for(; j + G(j) <= downIndex; j += G(j)) {
            result = max(result, right[i][j]);
        }
    }

    result = max(result, data[i-1][j-1]);

    for(i = rightIndex; i - G(i) >= leftIndex; i -= G(i)) {
        for(j = downIndex; j - G(j) >= upIndex; j -= G(j)) {
            result = max(result, left[i][j]);
        }
    }

    return result;
}