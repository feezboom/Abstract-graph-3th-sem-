#include "agraph.h"

#include <iostream>

/* ваша реализация графа, таких реализаций может быть несколько, подходящих для разных случаев */
template<typename V, typename E>
class Graph {
public:
    bool do_algorithm() {
        std::cout << "do algorithm for " << typeid(V).name() << "," << typeid(E).name() << std::endl;
		return true;
    }
    ~Graph() {}
};

/* ваша реализация фабричного метода */
AGraph* GraphFactory::makeGraph(Json::Value &){
    /* определяем подходящий тип графа для данного алгоритма */
	/* сюда же нужно добавить инициализацию */
    return new AGraph( Graph<int, double>() );
}
