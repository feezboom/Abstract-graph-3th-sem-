//
// Created by avk on 13.12.15.
//

#include "FenwickTree.h"
#include <cmath>

FenwickTree:: FenwickTree(vector<double> data) : data(data) {

    for(k = 0; pow(2,k) < data.size(); ++k);
    for(int i = 0; i < pow(2,k); ++i) {
        left.push_back(-1);
        right.push_back(-1);
    }

    prepare();
}

void FenwickTree::prepare() {
    for(int i = 0; i < data.size(); ++i) {
        update(i + 1, data[i]);
    }
}

void FenwickTree::update(int index, double value) {
    for(int i = index; i <= pow(2, k); i += G(i)) {
        left[i] = std::max(left[i], value);
    }

    for(int i = index; i > 0; i -= G(i)) {
        right[i] = std::max(right[i], value);
    }
}

double FenwickTree::getMax(int leftIndex, int rightIndex) {
    double result = 0;
    int i;
    for(i = leftIndex; i + G(i) <= rightIndex; i += G(i)) {
        result = std::max(result, right[i]);
    }

    if (data[i-1])
    result = std::max(result, data[i-1]);

    for(i = rightIndex; i - G(i) >= leftIndex; i -= G(i)) {
        result = std::max(result, left[i]);
    }

    return result;
}