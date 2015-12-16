//
// Created by avk on 14.12.15.
//

#ifndef WATERWAY_WATERWAYTESTING_H
#define WATERWAY_WATERWAYTESTING_H

#include "../jsoncpp/include/json/value.h"
#include "../Tasks/waterway/FenwickTree.h"
#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


int testWaterWay(string path, int left, int right, int up, int down);
#endif //WATERWAY_WATERWAYTESTING_H
