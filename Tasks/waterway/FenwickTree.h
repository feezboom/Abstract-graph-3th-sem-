//
// Created by avk on 13.12.15.
//

#ifndef WATERWAY_FENWICKTREE_H
#define WATERWAY_FENWICKTREE_H

#include <vector>
#include "../jsoncpp/include/json/json.h"

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

    vector<vector<int>> up;
    vector<vector<int>> down;

    int verticalPower;
    int horizontalPower;
    void prepare();
public:
    FenwickTree(vector<vector<int>> data);
    void update(int i, int j, int value);
    int getMin(int leftIndex, int rightIndex, int upIndex, int downIndex);
    void print();
};


#endif //WATERWAY_FENWICKTREE_H
