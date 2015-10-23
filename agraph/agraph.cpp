#include "agraph.h"

#include <iostream>

/* ваша реализация графа */
template<typename V, typename E>
class Graph {
public:
    bool do_algorithm() {
        std::cout << "do algorithm for " << typeid(V).name() << "," << typeid(E).name() << std::endl;
    }
    ~Graph() {}
};

/* ваша реализация фабричного метода */
AGraph* GraphFactory::makeGraph(Json::Value &){
    /* определяем подходящий тип графа для данного алгоритма */
    return new AGraph( Graph<int, double>() );
}
