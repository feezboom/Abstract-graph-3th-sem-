#ifndef _AGRAPH_H_
#define _AGRAPH_H_

#include <string>
#include <memory>
#include <vector>
#include "../jsoncpp/include/json/json.h"
#include "graphs_export.h"

using namespace std;

class AGraph {

	/* GraphConcept - общий интерфейc обобщенного класса граф */
    struct GraphConcept {

        virtual void insert_vertex(const string& name) = 0;
        virtual void add_edge(const string& from, const string& to, double weight = 0) = 0;
        virtual void transpose() = 0;
        virtual vector<vector<string>> getStrongComponents() = 0;

        virtual ~GraphConcept() {}
    };

    template<typename T>
    struct GraphModel : GraphConcept {
        GraphModel( const T& t ) : object( t ) {}
        virtual void insert_vertex(const string& name) {
            object.insert_vertex(name);
        }
        virtual void add_edge(const string& from, const string& to, double weight = 0) {
            object.add_edge(from, to, weight);
        }
        virtual void transpose() {
            object.transpose();
        }
        virtual vector<vector<string>> getStrongComponents() {
            object.Kosaraju();
        }


        virtual ~GraphModel() {}
    private:
        T object;
    };


/*    template<typename U>
    U cast() const
    {

        if(typeid(U) != type_info(object))
            throw std::runtime_error("Bad graph cast");
        return static_cast <GraphModel<U>* >(object)->object;
    }
*/

private:
    std::unique_ptr<GraphConcept> object;

public:
    template<typename T>
    AGraph(const T& obj):object( new GraphModel<T>( obj ) ) {}

    void insert_vertex(const string& name) {
        return object->insert_vertex(name);
    }
    void add_edge(const string& from, const string& to, double weight = 0) {
        return object->add_edge(from, to, weight);
    }
    void transpose() {
        return object->transpose();
    }
    vector<vector<string>> getStrongComponents() {
        return object->getStrongComponents();
    }
};




    /* это паттерн фабричный метод, что-то вроде виртуального конструктора */
class GRAPHS_EXPORT GraphFactory {
public:
    static AGraph* makeGraph(Json::Value& JSON_ROOT);
    static AGraph* makeGraph(string&, Json::Value& GRAPH_DATA_NOT_ROOT);

    virtual ~GraphFactory() = 0;
private:
    GraphFactory(){}
};


#endif //_AGRAPH_H_
