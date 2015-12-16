#include <vector>
#include "jsoncpp/include/json/json.h"
#include "agraph/agraph.h"

#include "testLibraries/waterwayTestLib.h"

#include "catch.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


SCENARIO("ZERO") {
    cout << "Initialized" << endl;
}

SCENARIO("waterway testing blam") {
    cout << "testing waterway" << endl;
    GIVEN("test0.json") {
        string test = "/home/avk/Documents/ninja_turtles/Tasks/waterway/tests/test0.json";
        int left, right, up, down;
        WHEN("Rectangle : (1,1), (3, 3)") {
            left = 1; right = 3; up = 1; down = 3;
            REQUIRE(testWaterWay(test, left, right, up, down) == 1);
        }
        WHEN("Another rectangle : (2,1), (3, 3)") {
            left = 2; right = 3; up = 1; down = 3;
            REQUIRE(testWaterWay(test, left, right, up, down) == 2);
        }
    }

}
