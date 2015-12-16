#include <vector>
#include "jsoncpp/include/json/json.h"
#include "agraph/agraph.h"

#include "Tasks/statemachine/StateMachineGraph.h"

#include "catch.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;


SCENARIO("ZERO") {
    cout << "Initialized" << endl;
}

SCENARIO("Statemachine testing (Ахо-Корасик)") {
    cout << "testing Aho-Korasik" << endl;
    StateMachineGraph ourGraph;
}
