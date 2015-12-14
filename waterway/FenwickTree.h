//
// Created by avk on 13.12.15.
//

#ifndef WATERWAY_FENWICKTREE_H
#define WATERWAY_FENWICKTREE_H

#include <vector>
#include <iostream>

using std::vector;

class FenwickTree {
public:
    static int G(int i) {
        return i - (i&(i-1));
    }
private:
    vector<vector<int>> data;
    vector<vector<int>> left;
    vector<vector<int>> right;
    int verticalPower;
    int horizontalPower;

    // В left[i] хранится максимум на отрезке [i - G(i) + 1, i], если i < pow(2,k), и data[i], если i = pow(2,k)
    // В right[i] хранится максимум на отрезке [i + G(i) -1], если i < pow(2, k), и data[i], если i = pow(2,k)
    // k - минимальное число, такое, что pow(2, k) >= data.size()
    void prepare();
public:
    FenwickTree(vector<vector<int>> data);
    FenwickTree(Json::Value value);
    void update(int i, int j, int value);
    int getMin(int leftIndex, int rightIndex, int upIndex, int downIndex);
    void print();
};


#endif //WATERWAY_FENWICKTREE_H
