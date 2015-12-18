#include <vector>
#include "jsoncpp/include/json/json.h"
#include "testLibraries/transportTestLib.h"
#include "agraph/agraph.h"

#include "catch.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


SCENARIO("ZERO") {
    cout << "Initialized" << endl;
}

SCENARIO("Testing transport task") {
    REQUIRE(solveOurTransportTask("test0.json") == 260);
    REQUIRE(solveOurTransportTask("test1.json") == 1);
}
