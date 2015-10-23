#include <vector>
#include "jsoncpp/include/json/json.h"
#include "agraph/agraph.h"

#include "catch.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

SCENARIO("scenario1"){
    std::ifstream ifs;
    Json::Value root;
    Json::Reader reader;

    ifs.open("../mipt/2sat.json", std::ifstream::in);
    bool res = reader.parse(ifs, root);
    REQUIRE( res != false );

    cout << "pairs:" << endl;

    Json::Value g = root["2sat"];
    for(int i = 0; i < g.size(); ++i){
        cout << g[i][0].asString() << " : " << g[i][1].asString() << endl;
    }

}

SCENARIO("scenario2"){
    std::ifstream ifs;
    Json::Value root;
    Json::Reader reader;

    ifs.open("../mipt/graph.json", std::ifstream::in);
    bool res = reader.parse(ifs, root);
    REQUIRE( res != false );

    /* создаем граф, подходящий под алгоритм (тип алгоритма описан в json) */
    std::unique_ptr<AGraph> g(GraphFactory::makeGraph(root));
    g->algorithm();

    /* тестируем со страшной силой */

    Json::Value r = root["graphs"][0]["graph"];
    cout << "nodes:" << endl;
    for (auto& n : r["nodes"]) {
        cout << n["id"].asString() << " : " << n["label"].asString() << endl;
    }

    cout << "edges:" << endl;
    for (auto& e : r["edges"]) {
        cout << e["source"].asString() << " -> " << e["target"].asString() << endl;
    }
}

SCENARIO("scenario3", "[tag1][tag2]"){
    GIVEN("vector"){
        std::vector<int> v( 5 );

        WHEN( "the size is increased" ) {
            v.resize( 10 );
            THEN( "the size and capacity change" ) {
                REQUIRE( v.size() == 10 );
                REQUIRE( v.capacity() >= 10 );
            }
        }
        WHEN( "nothing happened" ) {
            REQUIRE( v.size() != 5 ); //неправильная проверка
        }
    }
}
