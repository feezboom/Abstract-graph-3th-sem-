#include "2sat.h"

int main() {
    std :: cout << "2Sat local test started and finished." << endl;
    try {
        test2Sat("test0.json");
    }
    catch (string i) {
        std :: cout << "Error : " << i << std :: endl;
    }

    return 0;
}
