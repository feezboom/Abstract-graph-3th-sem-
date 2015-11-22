#include "agraph.h"
#include <iostream>
#include <typeinfo>

#include "MainGraph.h"
#include "TransportGraph.h"
#include "LandingGraph.h"



/* ваша реализация графа, таких реализаций может быть несколько, подходящих для разных случаев */
template<typename V, typename E>
class Graph {
public:
    void insert_vertex(const string& name) {
        return;
    }
    void add_edge(const string& from, const string& to, double weight = 0) {
        return;
    }
    void transpose() {
        return;
    }
    vector<vector<string>> Kosaraju() {
        return vector<vector<string>>();
    }


    ~Graph() {}
};


AGraph* GraphFactory::makeGraph(string name){
    if(name == "transport") {
        return new AGraph(CountryGraph <int, int>());
    }
    if(name == "landing") {
        return new AGraph(LandingGraph());
    }
}
