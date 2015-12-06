//
// Created by avk on 06.12.15.
//

#ifndef STATEMACHINE_STATEMACHINEGRAPH_H
#define STATEMACHINE_STATEMACHINEGRAPH_H

#include <map>
#include <vector>
#include <string>

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
    StateMachineGraph() {
        // Инициализация бора
        nodes.push_back(stateMachineVertex(-1, '\0'));
    }

    // Необходимые функции для паттерна графа
    void insert_vertex(const string& name) { insertPattern(name); }
    void add_edge(const string& from, const string& to, double weight = 0) { doNothing(); }
    void transpose() { doNothing();};
    vector<vector<string>> getStrongComponents() {
        return vector<vector<string>>();
    }

private:
    int getSmartSuffixLink(int v) {
        if (nodes[v].smartSuffixLink == -1) {
            int u = getSuffixLink(v);
            // Если обычная суффиксная ссылка от v указывает на корень
            if (u == 0) {
                nodes[v].smartSuffixLink = 0;
            } else {
                // А если указывает не на корень, то
                if (nodes[u].isWord) {
                    // если u соответствует слову в боре, то умная ссылка найдена
                    nodes[v].smartSuffixLink = u;
                } else {
                    // иначе, ищем умную ссылку от u
                    nodes[v].smartSuffixLink = getSmartSuffixLink(u);
                }
            }
        }
        return nodes[v].smartSuffixLink;
    }
    // Возвращает суффиксную ссылку заданной вершины
    int getSuffixLink(int v) {
        // Если суффиксной ссылки у этой вершины ещё нет, получим её
        if (nodes[v].suffixLink == -1) {
            // Если вершина - корень, или её предок - корень, то
            // её суффиксная ссылка - это корень.
            if (nodes[v].parent == 0 || v == 0)
                nodes[v].suffixLink = 0;
            else {
                nodes[v].suffixLink = getMove(getSuffixLink(nodes[v].parent), nodes[v].parentSymbol);
            }
        }
        return nodes[v].suffixLink;
    }
    // Возвращает самый оптимальный переход, с учётом суффиксных ссылок
    // из заданной вершины по заданному символу
    int getMove(int v, char ch) {
        // Это если оптимальный переход пока не задан. Зададим его.
        if (nodes[v].move.find(ch) == nodes[v].move.end()) {
            // Если есть ребёнок по символу ch
            if (nodes[v].child.find(ch) != nodes[v].child.end())
                // То этот переход будет по этому ребёнку
                nodes[v].move[ch] = nodes[v].child[ch];
            // А если ребёнка по символу ch нет
            else
                // Если это корень, то?? как так может быть
                if (v == 0)
                    nodes[v].move[ch] = 0;
                // Иначе переходим по суффиксной ссылке, и уже ищем там.
                else
                    nodes[v].move[ch] = getMove(getSuffixLink(v), ch);
        }
        return nodes[v].move[ch];
    }
    // Вставляет заданную строку в бор
    void insertPattern(const string &name) {
        // Вставка строки в бор
        int active = 0; // Все дела начинаются с корня
        for (int i = 0; i < name.length(); ++i) {
            char symbol = name[i];
            if (nodes[active].child.find(symbol) == nodes[active].child.end()) {
                // Значит, такого ребра не существует
                // Добавим его!
                nodes.push_back(stateMachineVertex(active, symbol));
                nodes[active].child[symbol] = (int)nodes.size() - 1;
            }
            active = nodes[active].child[symbol];
        }
        nodes[active].isWord = true;
        nodes[active].pattern = name;
    }
};


#endif //STATEMACHINE_STATEMACHINEGRAPH_H
