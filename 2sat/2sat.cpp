#include "2sat.h"
#include "../Graph/graph.h"
#include <cstdlib>

void makeNegative(string& label) {
    if (label.length() > 3 && label.substr(0, 3) == "not") {
         label = label.substr(3, label.length() - 3);
    } else {
        label = "not" + label;
    }
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
void printStrongComponents(vector <vector <string>> components) {
    for(const auto& component : components) {
        for(const auto& v : component) {
            cout << v << " ";
        }
        cout << endl;
    }
}
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

//Working with tests
void findTest(string name, std :: ifstream& ifs) {

    ifs.open("../2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../ninja_turtles/2sat/tests/" + name, std::ifstream::in);
    if(!ifs)
        ifs.open("../../2sat/tests/" + name, std::ifstream::in);
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
