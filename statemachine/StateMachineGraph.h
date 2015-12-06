//
// Created by avk on 06.12.15.
//

#ifndef STATEMACHINE_STATEMACHINEGRAPH_H
#define STATEMACHINE_STATEMACHINEGRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct stateMachineVertex {
    int parent;                 // Родительская вершина
    char parentSymbol;          // Символ перехода в эту вершину из родительской
    map <char, int> child;      // Массив дочерних вершин
    map <char, int> move;       // Массив переходов, включая суффиксные ссылки!!
    string pattern;             // Строка-паттерн, которая заканчивается на этой вершине
    bool isWord;                // Флаг наличия конца слова в этой вершине
    int suffixLink;             // Суффиксная ссылка
    int smartSuffixLink;        // Умная суффиксная ссылка, указывает на ближайшее
                                // по суффиксным ссылкам слово, содержащееся в боре

    stateMachineVertex(int parent, char parentSymbol) :
            pattern(""), isWord(false), suffixLink(-1),
            parent(parent), parentSymbol(parentSymbol),
            smartSuffixLink(-1) {};
};

class StateMachineGraph {
private:
    vector<stateMachineVertex> nodes;
    void doNothing() {};
public:
    // Конструктор графа
    StateMachineGraph();
    // Необходимые функции для паттерна графа
    void insert_vertex(const string& name) { insertPattern(name); }
    void add_edge(const string& from, const string& to, double weight = 0) { doNothing(); }
    void transpose() { doNothing();};
    vector<vector<string>> getStrongComponents() {
        doNothing();
        return vector<vector<string>>();
    }

    // Возвращает ответ в виде мультимапа - <строка, начала её вхождений>
    multimap <string, int> solve(string input);
private:
    // Возвращает умную суффиксную ссылку данной вершины
    int getSmartSuffixLink(int v);
    // Возвращает суффиксную ссылку заданной вершины
    int getSuffixLink(int v);
    // Возвращает самый оптимальный переход, с учётом суффиксных ссылок
    // из заданной вершины по заданному символу
    int getMove(int v, char ch);
    // Вставляет заданную строку в бор
    void insertPattern(const string &name);
};


#endif //STATEMACHINE_STATEMACHINEGRAPH_H
