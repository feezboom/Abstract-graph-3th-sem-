//
// Created by avk on 06.12.15.
//
#include <iostream>
#include "StateMachineGraph.h"
using std::cout;
// Конструктор графа
StateMachineGraph :: StateMachineGraph() {
    // Инициализация бора
    nodes.push_back(stateMachineVertex(-1, '\0'));
}
// Возвращает умную суффиксную ссылку данной вершины
int StateMachineGraph :: getSmartSuffixLink(int v) {
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
int StateMachineGraph :: getSuffixLink(int v) {
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
int StateMachineGraph :: getMove(int v, char ch) {
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
void StateMachineGraph :: insertPattern(const string &name) {
    // Вставка строки в бор
    int active = 0; // Все дела начинаются с корня
    for (int i = 0; i < name.length(); ++i) {
        // Пробегаемся по символам строки
        char symbol = name[i];
        if (nodes[active].child.find(symbol) == nodes[active].child.end()) {
            // Значит, ребра по такому символу не существует
            // Добавим его!
            nodes.push_back(stateMachineVertex(active, symbol));
            nodes[active].child[symbol] = (int)nodes.size() - 1;
        }
        // Переназначаем активную вершину
        active = nodes[active].child[symbol];
    }
    nodes[active].isWord = true;
    nodes[active].pattern = name;
}

// Возвращает ответ в виде мультимапа - <строка, начала её вхождений>
multimap <string, int> StateMachineGraph :: solve(string input) {
    int u = 0;
    multimap <string, int> answer;
    for (int i = 0; i < input.length(); ++i) {
        u = getMove(u, input[i]);
        for (int v = u; v != 0; v = getSmartSuffixLink(v)) {
            if (nodes[v].isWord) {
                answer.insert(make_pair(nodes[v].pattern, i - nodes[v].pattern.length() + 2));
                cout << nodes[v].pattern << " " << i - nodes[v].pattern.length() + 2 << endl;
            }
        }
    }
    return answer;
}
