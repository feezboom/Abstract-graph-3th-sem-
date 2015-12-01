#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Node {
    int leftIndex, rightIndex, parentNode, suffixLink;
    map<char,int> childrenNodes;

//Constructor
    Node (int l=0, int r=0, int par=-1)
        : leftIndex(l), rightIndex(r), parentNode(par), suffixLink(-1) {}
//Getiing length of substr "written" edge to parent from this node
    int getEdgeLength() {
        return rightIndex - leftIndex;
    }

    int &get (char symbol) {
        if (!childrenNodes.count(symbol))
            childrenNodes[symbol] = -1;

        return childrenNodes[symbol];
    }
};

struct State {
    int vertex, position;

//constructor
    State (int v, int pos) : vertex(v), position(pos) {}
};



const int MaxTreeSize = 1000000;
string inputString = "xabxa";
Node ourTree[MaxTreeSize];
State ptr(0, 0);
int treeSize;
int n;



State go(State st, int l, int r) {
    while (l < r)
        if (st.position == ourTree[st.vertex].getEdgeLength()) {
            st = State (ourTree[st.vertex].get( inputString[l] ), 0);
            if (st.vertex == -1)  return st;
        }
        else {
            if (inputString[ ourTree[st.vertex].leftIndex + st.position ] != inputString[l])
                return State (-1, -1);
            if (r-l < ourTree[st.vertex].getEdgeLength() - st.position)
                return State (st.vertex, st.position + r-l);
            l += ourTree[st.vertex].getEdgeLength() - st.position;
            st.position = ourTree[st.vertex].getEdgeLength();
        }
    return st;
}

int split (State currentState) {
    if (currentState.position == ourTree[currentState.vertex].getEdgeLength())
        return currentState.vertex;
    if (currentState.position == 0)
        return ourTree[currentState.vertex].parentNode;
    Node v = ourTree[currentState.vertex];
    int id = treeSize++;
    ourTree[id] = Node (v.leftIndex, v.leftIndex+currentState.position, v.parentNode);
    ourTree[v.parentNode].get( inputString[v.leftIndex] ) = id;
    ourTree[id].get( inputString[v.leftIndex + currentState.position] ) = currentState.vertex;
    ourTree[currentState.vertex].parentNode = id;
    ourTree[currentState.vertex].leftIndex += currentState.position;
    return id;
}

int get_link (int vertex) {
    if (ourTree[vertex].suffixLink != -1) return ourTree[vertex].suffixLink;
    if (ourTree[vertex].parentNode == -1)  return 0;

    int to = get_link(ourTree[vertex].parentNode);

    return ourTree[vertex].suffixLink = split(go(State(to,ourTree[to].getEdgeLength()), ourTree[vertex].leftIndex + (ourTree[vertex].parentNode==0), ourTree[vertex].rightIndex));
}

void tree_extend (int index) {
    for(;;) {
        State nptr = go(ptr, index, index+1);
        if (nptr.vertex != -1) {
            ptr = nptr;
            return;
        }

        int mid = split(ptr);
        int leaf = treeSize++;
        ourTree[leaf] = Node(index, n, mid);
        ourTree[mid].get(inputString[index]) = leaf;

        ptr.vertex = get_link (mid);
        ptr.position = ourTree[ptr.vertex].getEdgeLength();
        if (!mid) break;
    }
}

void build_tree() {
    treeSize = 1;
    for (int i=0; i<n; ++i)
        tree_extend(i);
}


int main() {
	std::cout << "Hello, World!" << std::endl;
    build_tree();
	return 0;
}
