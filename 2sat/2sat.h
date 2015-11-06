#ifndef _2SAT_H_
#define _2SAT_H_

#include <string>
#include <vector>
#include <string>
#include "fstream"
#include <iostream>
#include "../Graph/graph.h"
#include "jsoncpp/include/json/json.h"



struct Variable {
    string label;
    bool negative;
    Variable() {
        this->label = "";
        this->negative = false;
    }
    Variable(string label, bool negative) {
        this->label = label;
        this->negative = negative;
    }
};
bool isProblem(vector <string> strongComponent);
bool solve_2sat(vector <std::pair <Variable, Variable>> disjunkts);
void makeNegative(string& label);
bool isProblem(vector <string> strongComponent);
void printStrongComponents(vector <vector <string>> components);
bool solve_2sat(vector <std::pair <Variable, Variable>> disjunkts);

void findTest(string name, std :: ifstream& ifs);
bool test2Sat(string testName);

//Не могу вынести имплементацию test2Sat в 2sat.cpp
//линкёр говорит что реализация библиотечных методов json не найдена
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
#endif
