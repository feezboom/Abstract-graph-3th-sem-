#include <iostream>
#include "agraph.h"
#include "agraph_export.h"
#include "../jsoncpp/include/json/json.h"

using std::cout;
using std::endl;

int main() {
    std::cout << "Hello, agraph!" << std :: endl;

    vector<int> v{0,1,2,3,4,5,6,7,8,9,10,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};

    for(auto i : v) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
