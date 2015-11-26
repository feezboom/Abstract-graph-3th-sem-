#include <vector>
#include "jsoncpp/include/json/json.h"
#include "2sat.h"
#include "salesman.h"
#include "Graph/graph.h"
#include "agraph/agraph.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

string getTaskName(string testPath) {
    std::ifstream ifs;
    Json::Value root;
    Json::Reader reader;

    ifs.open(testPath, std::ifstream::in);
    REQUIRE(ifs);

    bool res = reader.parse(ifs, root);
    REQUIRE(res != false);

    if (root["salesman"] != Json::Value::null)
        return "salesman";
    else if (root["2sat"] != Json::Value::null)
        return "2sat";
    else  if (root["landing"] != Json::Value::null)
        return "landing";
    else
        return "null";
}

SCENARIO("Testing 2sat task") {
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

SCENARIO("test") {
    string testPath = "../../salesman/tests/test0.json";

    string name = getTaskName(testPath);

    if (name == "salesman") {
        REQUIRE(testSalesman(testPath) == 234);
    }

}
