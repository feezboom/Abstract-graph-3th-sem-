//
// Created by avk on 14.12.15.
//

#include "waterwayTestLib.h"
#include <cmath>
#include <limits.h>

int testWaterWay(Json::Value &value){
    FenwickTree fenwickTree(value);
}

FenwickTree::FenwickTree(Json::Value value) {
    Json::Value g = value["xdim"];
    int xdim = g.asInt();
    g = value["ydim"];
    int ydim = g.asInt();
    g = value["data"];

    this->data.resize(ydim, vector<int>(xdim, 0));

    for(int i = 0; i < ydim; ++i) {
        for(int j = 0; j < xdim; ++j) {
            this->data[i][j] = g[i][j].asInt();
        }
    }
    // Preparing;
    prepare();
}

int testWaterWay(string path, int left, int right, int up, int down) {
    std::ifstream ifs;
    Json::Value root;
    Json::Reader reader;

    ifs.open(path, std::ifstream::in);
    bool res = reader.parse(ifs, root);
    if (res == false) {
        throw "mistake in json test file (" + path + ")";
    }

    FenwickTree fenwickTree(root);
//    cout << left << right << up << down << endl;
    return fenwickTree.getMin(left, right, up, down);
    return 0;

}
