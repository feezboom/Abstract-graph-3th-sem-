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


#include <float.h>
#include <map>
#include <set>
#include <vector>


using namespace std;

template <class V, class E>
class Graph {
protected:
    vector<V> vertices;
    map<V, map<V, E>> edges;
    bool vertexInGraph(V v);
public:
    Graph();
    virtual void insertVertex(const V &v);
    void addEdge(const V &v1, const V &v2, const E &e);
    void printGraph();
    E do_Dijkstra(const V &v1, const V &v2);

protected:
    E getEdge(const V &v1, const V &v2) {
        if (!vertexInGraph(v1) || !vertexInGraph(v2)) {
            throw "Одной из вершин нет в графе!";
        }
        return edges[v1][v2];
    }
public:
    typedef typename vector<V>::iterator Iterator;
    Iterator begin() {
        return vertices.begin();
    }
    Iterator end() {
        return vertices.end();
    }
};


template<class V, class E>
E Graph<V, E>::do_Dijkstra(const V &v1, const V &v2) {
    if (!vertexInGraph(v1) || !vertexInGraph(v2))
        return DBL_MAX;

    multiset <pair<E, V>> pq;

    map <V, E> cost;

    double inf = DBL_MAX - 1;
    for (auto &it : vertices)
        cost[it] = inf;

    cost[v1] = 0;
    pq.insert(make_pair(0, v1));

    while(!pq.empty()) {
        V father = pq.begin()->second;

        pq.erase(pq.begin());

        auto children = edges[father];
        for (auto it : children) {
            V child = it.first;
            if (cost[child] > cost[father] + edges[father][child]) {
                pq.erase(make_pair(cost[child], child));
                cost[child] = cost[father] + edges[father][child];
                pq.insert(make_pair(cost[child], child));
            }
        }
    }
    return cost[v2];
}

template<class V, class E>
Graph<V, E>::Graph() {};

template<class V, class E>
void Graph<V, E>::printGraph() {
    for(const auto &it : vertices) {
        cout << "VERTEX " << it.source << it.type<< endl;
        for (const auto &j : edges[it]) {
            cout << it.source << it.type << "-->" << j.first.source << j.first.type << " cost : " << j.second << " " << endl;
        }
    }
}

template <class V, class E>
void Graph<V, E>::insertVertex(const V &v) {
    if (vertexInGraph(v))
        cerr << "Вершина в графе уже есть!\n";
    else
        vertices.push_back(v);
}

template <class V, class E>
bool Graph<V, E>::vertexInGraph(V v) {
    for (const auto &it : vertices) {
        if (it == v)
            return true;
    }
    return false;
}

template <class V, class E>
void Graph<V, E>::addEdge(const V &v1, const V &v2, const E &e) {
    if (!vertexInGraph(v1) || !vertexInGraph(v2)) {
        cerr << "Нет вершины для создания ребра" << endl;
    }
    edges[v1][v2] = e;
}






















template <class V, class E>
class Tree : protected Graph<V, E> {
private:
    long rootNumber;
    typedef typename map<V, E>::iterator ChildrenIterator;
public:
    Tree() {
        rootNumber = -1;
    }
    void insertRoot(const V &v) {
        if (rootNumber == -1) {
            this->vertices.push_back(v);
            rootNumber = this->vertices.size();
        } else
            cerr << "Корень у дерева уже существует!" << endl;
    }
    void addChild(const V &parent, const V &child, const E &e) {
        if (!(this->vertexInGraph(parent))) {
            cerr << "Такого родителя не существует!" << endl;
            return;
        } else if (this->vertexInGraph(child)) {
            cerr << "Ребенок уже в графе!" << endl;
            return;
        }

        this->vertices.push_back(child);
        this->edges[parent][child] = e; //Если что, то проверять эту строчку.
    }
    void printTree() {
        this->printGraph();
    }
    E getBranch(const V &v1, const V &v2) {
        return this->getEdge(v1, v2);
    }
    typename Graph<V, E> :: Iterator treeBegin() {
        return this->vertices.begin();
    }
    typename Graph<V, E> :: Iterator treeEnd() {
        return this->vertices.end();
    }
    ChildrenIterator childrenBegin(const V &v) {
        if(!(this->vertexInGraph(v)))
            return map<V, E>().end();
        return this->edges[v].begin();
    }
    ChildrenIterator childrenEnd(const V &v) {
        if (!(this->vertexInGraph(v)))
            return map<V, E>().end();
        return this->edges[v].end();
    }
    typename Graph<V, E> :: Iterator find(const V &v) {
        for(auto it = this->vertices.begin(); it != this->vertices.end(); ++it) {
            if (*it == v)
                return it;
        }
    };
};




using namespace std;

struct stateMachineVertex {
    int id;
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
            smartSuffixLink(-1) {
        static int count = 0;
        id = count++;
    };
    bool operator==(const stateMachineVertex &v) const {
        return (id == v.id);
    }
    bool operator<(const stateMachineVertex &v) const {
        if (parentSymbol < v.parentSymbol)
            return true;
        else if (parentSymbol == v.parentSymbol)
            return parent < v.parent;
        else return false;
/*        if (pattern < v.pattern)
            return true;
        else if (pattern == v.pattern)
//            return parent < v.parent;
//        else if (parent == v.parent)
            return parentSymbol < v.parentSymbol;
        else if (parentSymbol == v.parentSymbol)
            return isWord < v.isWord;
        else if (isWord == v.isWord)
            return suffixLink < v.suffixLink;
        else if (suffixLink == v.suffixLink)
            return smartSuffixLink < v.smartSuffixLink;
        else if (smartSuffixLink == v.smartSuffixLink)
            return parent < v.parent;
        else if (parent == v.parent)
            return parentSymbol < v.parentSymbol;
            */
    }
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
    void transpose() { doNothing();}
    vector<vector<string>> getStrongComponents() {
        doNothing();
        return vector<vector<string>>();
    }
    void print_graph() { doNothing();};

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
