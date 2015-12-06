#include <string>
#include <map>
#include <iostream>

struct vertex;
struct edge {
    size_t beg;
    size_t lim;
    vertex *end;
    edge():beg(0),lim(0),end(0){};
};
struct vertex {
    std::map <char,edge> child;
    size_t id_dontuse;
    size_t depth_dontuse;
    vertex *suffix_link;
};

#define min(x,y) ((x<y)?(x):(y))

int main(void) {
    return 0;
}