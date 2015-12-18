#include "2sat.h"
#include "../../agraph/agraph.h"

bool solve_2sat(vector <std::pair <Variable, Variable>> disjunkts) {

    graph_list <int, int> our2SatGraph;

    for (const auto& it : disjunkts) {
        string v1 = ((it.first.negative) ? "" : "not") + it.first.label; //this is because of replacing disjunct to implication
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

bool isProblem(vector <string> strongComponent) {
    while (!strongComponent.empty()) {
        string temp = *(--strongComponent.end());
        strongComponent.pop_back();

        string check = temp;
        makeNegative(check);

        for (const auto& it : strongComponent) {
            if (it == check)
                return true;
        }
    }
    return false;
}

void makeNegative(string& label) {
    if (label.length() > 3 && label.substr(0, 3) == "not") {
         label = label.substr(3, label.length() - 3);
    } else {
        label = "not" + label;
    }
}
