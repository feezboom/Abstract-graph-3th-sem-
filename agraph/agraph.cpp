#include "agraph.h"
#include "graphs.h"
#include <iostream>
#include <typeinfo>


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
}
