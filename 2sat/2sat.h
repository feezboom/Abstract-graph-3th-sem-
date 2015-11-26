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


#endif
