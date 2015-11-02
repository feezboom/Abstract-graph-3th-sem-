#ifndef _2SAT_H_
#define _2SAT_H_

#include <iostream>
#include <string>
#include "../Graph/graph.h"
#include "fstream"
#include <vector>
#include <string>

struct Variable;
bool isProblem(vector <string> strongComponent);
bool solve_2sat(vector <std::pair <Variable, Variable>> disjunkts);


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

bool isProblem(vector <string> strongComponent) {
    while (!strongComponent.empty()) {

        string temp = *(strongComponent.cbegin());
        strongComponent.pop_back();

        string check;
        if (temp.length() > 3 && temp.substr(0, 3) == "not") {
             check = "not" + temp;
        } else {
            check = temp;
        }
//        cout << "Here is TEMP!!!!!!!!!" << temp << endl;
        for (const auto& it : strongComponent) {
            if (it == check)
                return true;
        }
    }
    return false;
}

bool solve_2sat(vector <std::pair <Variable, Variable>> disjunkts) {

    graph_list <int, int> our2SatGraph;
    our2SatGraph.insert_vertex("Hello");
    for (const auto& it : disjunkts) {
        string v1 = ((it.first.negative) ? "not" : "") + it.first.label;
        string v2 = ((it.second.negative) ? "not" : "") + it.second.label;
        our2SatGraph.insert_vertex(v1);
        our2SatGraph.insert_vertex(v2);
        our2SatGraph.add_edge(v1, v2);
    }

    auto strongComponents = our2SatGraph.Kosaraju();
    for(const auto& it : strongComponents) {
        if (isProblem(it)) {
            return false;
        }
    }
    return true;
}

#endif
