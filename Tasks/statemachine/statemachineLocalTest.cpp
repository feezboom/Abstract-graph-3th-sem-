#include <string>
#include <iostream>
#include "StateMachineGraph.h"

using namespace std;

stateMachineVertex& findVertexById(int id, Tree<stateMachineVertex, char> &tree) {
    for(auto it = tree.treeBegin(); it != tree.treeEnd(); ++it) {
        if (it->id == id)
            return *it;
    }
}
int getMove(Tree<stateMachineVertex, char> &tree, int v, char symbol);
int getSuffixLink(Tree<stateMachineVertex, char> &tree, int v);

int getSuffixLink(Tree<stateMachineVertex, char> &tree, int v) {
    auto ourVertex = findVertexById(v, tree);
    // Если суффиксной ссылки ещё нет, то нужно её сделать
    if (ourVertex.suffixLink == -1) {
        // Если она сама, или родитель её - корень, то суф ссылка - корень
        if (ourVertex.parent == 0 || ourVertex.id == 0)
            ourVertex.suffixLink = 0;
        else
            ourVertex.suffixLink =
                    getMove(tree, getSuffixLink(tree, ourVertex.parent), ourVertex.parentSymbol);
    }
}

int getMove(Tree<stateMachineVertex, char> &tree, int v, char ch) {
    auto ourVertex = findVertexById(v, tree);
    // Если перехода ещё нет
    if (ourVertex.move.find(ch) == ourVertex.move.end()) {
        // Если есть ребёнок по символу ch
        if (ourVertex.child.find(ch) != ourVertex.child.end())
            ourVertex.move[ch] = ourVertex.child[ch];
        else if (v == 0)
            ourVertex.move[ch] = 0;
        else
            ourVertex.move[ch] = getMove(tree, getSuffixLink(tree, v), ch);
    }
    return ourVertex.move[ch];
}

int getSmartSuffixLink(Tree<stateMachineVertex, char> &tree, int v) {
    auto ourVertex = findVertexById(v, tree);
    if (ourVertex.smartSuffixLink == -1) {
        int u = getSuffixLink(tree, v);
        if (u == 0)
            ourVertex.smartSuffixLink = 0;
        else if (ourVertex.isWord)
            ourVertex.smartSuffixLink = u;
        else
            ourVertex.smartSuffixLink = getSmartSuffixLink(tree, u);
    }
    return ourVertex.smartSuffixLink;
}

void insertPattern(Tree<stateMachineVertex, char> &ourTree, string name) {
    auto active = findVertexById(0, ourTree);
    for (int i = 0; i < name.length(); ++i) {
        try {
            char symbol = name[i];
            auto it = ourTree.childrenBegin(active);
            for (; it != ourTree.childrenEnd(active); ++it)
                if ((*it).second == symbol)
                    break;
            // Значит, ребра по такому символу не существует
            // Добавим его!
            stateMachineVertex child(-1, 1);
            if (it == ourTree.childrenEnd(active)) {
                child = stateMachineVertex(active.id, symbol);
                ourTree.addChild(active, child, symbol);
                active = child;
            } else {
                child = it->first;
                active = child;
            }
        } catch (const char *i) {
            cerr << i << endl;
        }
    }
    ourTree.find(active)->pattern = name;
    ourTree.find(active)->isWord = true;
}

int main(void) {
    cout << "Hello, StateMachine!" << endl;
 /*   StateMachineGraph ourGraph;

    ourGraph.insert_vertex("abc");
    ourGraph.insert_vertex("bcdc");
    ourGraph.insert_vertex("cccb");
    ourGraph.insert_vertex("bcdd");
    ourGraph.insert_vertex("bbbc");

    ourGraph.solve("abcdcbcddbbbcccbbbcccbb");
    cout << endl;
    ourGraph.solve("abcdc");
*/
    vector<string> input {"abc", "bcdc", "cccb", "bcdd", "bbbc"};
    string str = "abcdcbcddbbbcccbbbcccbb";

    Tree <stateMachineVertex, char> ourTree;

    stateMachineVertex active = stateMachineVertex(-1, '\0');
    ourTree.insertRoot(active);



    // Инициализация бора
    for (int j = 0; j < input.size(); ++j) {
        string name = input[j];



        active.pattern = name;
        active.isWord = true;
        cout << j <<endl;
    }
    return 0;
}