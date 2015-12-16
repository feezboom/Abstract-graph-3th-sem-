#include <vector>
#include "jsoncpp/include/json/json.h"
#include "agraph/agraph.h"

#include "testLibraries/2satTestLib.h"

#include "catch.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


SCENARIO("ZERO") {
    cout << "Initialized" << endl;
}

SCENARIO("2sat_testing") {
    REQUIRE(test2Sat("test0.json") == true);
    REQUIRE(test2Sat("test1.json") == false);
    REQUIRE(test2Sat("test2.json") == false);
    REQUIRE(test2Sat("test3.json") == true);
    REQUIRE(test2Sat("test4.json") == true);
    REQUIRE(test2Sat("2sat.json") == true);
}
