#include "agraph.h"

#include <iostream>

/* ваша реализация графа, таких реализаций может быть несколько, подходящих для разных случаев */
#include "MainGraph.hpp"

/* ваша реализация фабричного метода */
AGraph* GraphFactory::makeGraph(Json::Value &value){
    /* определяем подходящий тип графа для данного алгоритма */
	/* сюда же нужно добавить инициализацию */
    //return new AGraph( Graph<int, double>() );
    Json::Value task;
    task = value["2sat"];

	return nullptr;
}
