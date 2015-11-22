#include <iostream>
#include "agraph.h"
#include "agraph_export.h"
#include "../jsoncpp/include/json/json.h"


int main() {
    std::cout << "Hello, agraph!" << std :: endl;

    GraphFactory ::makeGraph()->algorithm();


    return 0;
}
