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
    int lastBit(int x) {
        if (x != 1)
            return x - x&(x - 1);
        else
            return 1;
    }
private:
    vector<vector<int>> data;

    vector<vector<int>> redRed;
    vector<vector<int>> greenGreen;

    vector<vector<int>> redGreen;
    vector<vector<int>> greenRed;

    void prepare();
public:
    FenwickTree(vector<vector<int>> data);


    void updateGreenGreen();
    void updateGreenRen();
    void updateRedGreen();
    void updateRedRed();

    int getMin(int leftIndex, int rightIndex, int upIndex, int downIndex);
    void print();
};


#endif //WATERWAY_FENWICKTREE_H
