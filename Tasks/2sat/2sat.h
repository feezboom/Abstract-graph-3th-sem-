#ifndef _2SAT_H_
#define _2SAT_H_

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "../../agraph/MainGraph.hpp"


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
bool solve_2sat(vector <std::pair <Variable, Variable>> disjunkts);
bool isProblem(vector <string> strongComponent);
void makeNegative(string& label);
bool isProblem(vector <string> strongComponent);

#endif // _2SAT_H_

