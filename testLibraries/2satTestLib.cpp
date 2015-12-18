#include "../Tasks/2sat/2sat.h"
#include "2satTestLib.h"
#include "../agraph/MainGraph.hpp"
#include "../agraph/agraph.h"
#include "../jsoncpp/include/json/json.h"


void printStrongComponents(vector <vector <string>> components) {
    for(const auto& component : components) {
        for(const auto& v : component) {
            cout << v << " ";
        }
        cout << endl;
    }
}


//Working with tests
void findTest(string name, std :: ifstream& ifs) {

    ifs.open("../2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../../2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../ninja_turtles/Tasks/2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        throw "test file " + name + " was not found";
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

    for(int i = 0; i < g.size(); ++i) {
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

bool solve2Sat(Json::Value &value) {
    Json::Value task = value;
    AGraph* ourGraph = GraphFactory::makeGraph(task);
}

