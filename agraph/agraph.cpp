#include "agraph.h"

#include <iostream>

/* ваша реализация графа, таких реализаций может быть несколько, подходящих для разных случаев */
#include "MainGraph.hpp"

/* ваша реализация фабричного метода */
AGraph* GraphFactory::makeGraph(Json::Value &value){
    Json::Value task;
    task = value["2sat"];
    if (task != Json::nullValue) {
        return new AGraph(graph_list<int, int>());
    }

	return nullptr;
}
