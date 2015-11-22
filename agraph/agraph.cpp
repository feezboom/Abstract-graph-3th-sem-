#include "agraph.h"

#include <iostream>
#include <typeinfo>

/* ваша реализация графа, таких реализаций может быть несколько, подходящих для разных случаев */
template<typename V, typename E>
class PlaneGraph {
public:
    bool do_algorithm() {
        std::cout << "do algorithm for " << typeid(V).name() << "," << typeid(E).name() << std::endl;
		return true;
    }
    ~PlaneGraph() {}
};

/* ваша реализация фабричного метода */
AGraph* GraphFactory::makeGraph(Json::Value &){
    /* определяем подходящий тип графа для данного алгоритма */
	/* сюда же нужно добавить инициализацию */
    return new AGraph( PlaneGraph<unsigned char, double>() );
}


AGraph* GraphFactory::makeGraph(){
    /* определяем подходящий тип графа для данного алгоритма */
    /* сюда же нужно добавить инициализацию */
    return new AGraph( PlaneGraph<unsigned char, double>() );
}
