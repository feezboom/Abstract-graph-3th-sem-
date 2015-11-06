#include <vector>
#include "jsoncpp/include/json/json.h"
#include "2sat/2sat.h"
#include "Graph/graph.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

SCENARIO("Testing 2sat task"){
    try {
        REQUIRE(test2Sat("test0.json") == true);
        REQUIRE(test2Sat("test1.json") == false);
        REQUIRE(test2Sat("test2.json") == false);
        REQUIRE(test2Sat("test3.json") == true);
        REQUIRE(test2Sat("test4.json") == true);
        REQUIRE(test2Sat("2sat.json") == true);
    }
    catch(string error) {
        cout << "test error : " << error << endl;
        exit(1);
    }
}

