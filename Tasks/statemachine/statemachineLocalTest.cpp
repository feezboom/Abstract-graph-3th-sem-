#include <string>
#include <iostream>
#include "StateMachineGraph.h"

using namespace std;

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
    string name = "abcdcbcddbbbcccbbbcccbb";

    Tree <stateMachineVertex, char> ourTree;

    // Инициализация бора
    ourTree.insertRoot(stateMachineVertex(-1, '\0'));


    int active = 0;
    for (int i = 0; i < name.length(); ++i) {
        char symbol = name[i];

    }

    return 0;
}