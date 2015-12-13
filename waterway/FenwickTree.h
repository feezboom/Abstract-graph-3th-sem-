//
// Created by avk on 13.12.15.
//

#ifndef WATERWAY_FENWICKTREE_H
#define WATERWAY_FENWICKTREE_H

#include <vector>
using std::vector;

class FenwickTree {
public:
    static int G(int i) {
        return i - i&(i-1);
    }
private:
    vector<double> data;
    // В left[i] хранится максимум на отрезке [i - G(i) + 1, i], если i < pow(2,k), и data[i], если i = pow(2,k)
    vector<double> left;
    // В right[i] хранится максимум на отрезке [i + G(i) -1], если i < pow(2, k), и data[i], если i = pow(2,k)
    vector<double> right;
    // k - минимальное число, такое, что pow(2, k) >= data.size()
    int k;
    void prepare();
public:
    FenwickTree(vector<double> data);
    void update(int i, double value);
    double getMax(int leftIndex, int rightIndex);
};


#endif //WATERWAY_FENWICKTREE_H
