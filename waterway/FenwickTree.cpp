//
// Created by avk on 13.12.15.
//

#include "FenwickTree.h"
#include <cmath>
#include <limits.h>

using namespace std;

#define min(a,b) ((a) < (b) ? (a) : (b))

FenwickTree:: FenwickTree(vector<vector<int>> data) : data(data) {
    for(verticalPower = 0; pow(2, verticalPower) < data.size(); ++verticalPower);
    for(horizontalPower = 0; pow(2, horizontalPower) < data[0].size(); ++horizontalPower);

    for(int i = 0; i <= pow(2, verticalPower); ++i) {
        left.push_back(vector<int>());
        right.push_back(vector<int>());
        for(int j = 0; j <= pow(2, horizontalPower); ++j) {
            left[i].push_back(INT_MAX);
            right[i].push_back(INT_MAX);
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
    int i = indexI, j = indexJ;
    for(; i <= left.size(); i += G(i))
        for(; j <= left[i].size(); j += G(j))
            left[i][j] = min(left[i][j], value);

    i = indexI, j = indexJ;
    for(; i > 0; i -= G(i))
        for(; j > 0; j -= G(j))
            right[i][j] = min(right[i][j], value);

}

int FenwickTree::getMin(int leftIndex, int rightIndex, int upIndex, int downIndex) {
    int i = upIndex, j = leftIndex;
    int result = INT_MAX;

    for(; i + G(i) <= downIndex; i += G(i)) {
        for(; j + G(j) <= rightIndex; j += G(j)) {
            result = min(result, right[i][j]);
        }
    }

    result = min(result, data[i-1][j-1]);
    i = downIndex, j = rightIndex;

    for(; i - G(i) >= upIndex; i -= G(i))
        for(; j - G(j) >= leftIndex; j -= G(j))
            result = min(result, left[i][j]);

    return result;
}

void FenwickTree::print() {
    std::cout << "Left : " << std::endl;
    for(int i = 0; i < left.size(); ++i) {
        for(int j = 0; j < left[i].size(); ++j) {
            std::cout << left[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std :: cout << std::endl;
    std::cout << "Right : " << std::endl;
    for(int i = 0; i < right.size(); ++i) {
        for(int j = 0; j < right[i].size(); ++j) {
            std::cout << right[i][j] << " ";
        }
        std::cout << std::endl;
    }
}