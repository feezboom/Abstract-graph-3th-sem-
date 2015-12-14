//
// Created by avk on 14.12.15.
//

#ifndef WATERWAY_WATERWAYTESTING_H
#define WATERWAY_WATERWAYTESTING_H

#include "../jsoncpp/include/json/value.h"
#include "FenwickTree.h"
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


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
    return fenwickTree.getMin(left, right, up, down);

}
#endif //WATERWAY_WATERWAYTESTING_H
