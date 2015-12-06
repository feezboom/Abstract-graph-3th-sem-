//
// Created by avk on 06.12.15.
//

#ifndef STATEMACHINE_STATEMACHINEGRAPH_H
#define STATEMACHINE_STATEMACHINEGRAPH_H

#include <map>
#include <vector>

using namespace std;

class stateMachineVertex {
    map <char, int> child;      // Массив дочерних вершин
    int patternNumber;          // Номер строки паттерна, которая заканчивается на этой вершине
    bool isWord;                // Флаг наличия конца слова в этой вершине
};

class stateMachineGraph {
private:
    vector<stateMachineVertex> vertices;
public:

};


#endif //STATEMACHINE_STATEMACHINEGRAPH_H
