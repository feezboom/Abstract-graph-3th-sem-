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
        return i - (i&(i-1));
    }
private:
    vector<double> data;
    vector<double> left;
    vector<double> right;
    int k;
    // В left[i] хранится максимум на отрезке [i - G(i) + 1, i], если i < pow(2,k), и data[i], если i = pow(2,k)
    // В right[i] хранится максимум на отрезке [i + G(i) -1], если i < pow(2, k), и data[i], если i = pow(2,k)
    // k - минимальное число, такое, что pow(2, k) >= data.size()
    void prepare();
public:
    FenwickTree(vector<double> data);
    void update(int i, double value);
    double getMax(int leftIndex, int rightIndex);
};


#endif //WATERWAY_FENWICKTREE_H
