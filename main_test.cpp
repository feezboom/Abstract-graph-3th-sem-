#include <vector>
#include "jsoncpp/include/json/json.h"
#include "2sat/2sat.h"
#include "Graph/graph.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void findTest(string name, std :: ifstream& ifs) {
    ifs.open("../2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../ninja_turtles/2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        throw "test file" + name + " was not found";
}

bool test2Sat(string testName) {
    std::ifstream ifs;
    Json::Value root;
    Json::Reader reader;

    findTest(testName, ifs);

    bool res = reader.parse(ifs, root);
    if (res == false) {
        throw "mistake in json test file (" + testName + ")";
    }

    Json::Value g = root["2sat"];

    vector <std::pair<Variable, Variable>> data;

    for(int i = 0; i < g.size(); ++i){
        Variable var1, var2;
        Json::Value temp = g[i]["first"];

        var1.label = temp["label"].asString();
        var1.negative = temp["neg"].asBool();

        temp = g[i]["second"];
        var2.label = temp["label"].asString();
        var2.negative = temp["neg"].asBool();

        data.push_back(std::pair<Variable, Variable> (var1, var2));
    }

    bool answer = solve_2sat(data);
    if(answer) {
        cout << "test " + testName + " has at least one solution" << endl;
    } else {
        cout << "test " + testName + " hasn't got any solutions" << endl;
    }
    return answer;
}


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

