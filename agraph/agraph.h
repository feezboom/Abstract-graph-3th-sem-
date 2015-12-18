#ifndef AGRAPH
#define AGRAPH

#include <string>
#include <memory>
#include "../jsoncpp/include/json/json.h"

using std::string;
using std::vector;

class AGraph {

    /* GraphConcept - общий интерфейc обобщенного класса граф */
    struct GraphConcept {

        virtual void insert_vertex(const string& name) = 0;
        virtual void add_edge(const string& from, const string& to, double weight = 0) = 0;
        virtual void transpose() = 0;
        virtual vector<vector<string>> getStrongComponents() = 0;
        virtual void print_graph() = 0;

        virtual ~GraphConcept() {}
    };

    template<typename T>
    struct GraphModel : GraphConcept {
        GraphModel( const T& t ) : object( t ) {}
        virtual void insert_vertex(const string& name) {
            return object.insert_vertex(name);
        }
        virtual void add_edge(const string& from, const string& to, double weight = 0) {
            return object.add_edge(from, to, weight);
        }
        virtual void transpose() {
            return object.transpose();
        }
        virtual vector<vector<string>> getStrongComponents() {
            return object.Kosaraju();
        }
        virtual void print_graph() {
            return object.print_graph();
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
    void print_graph() {
        return object->print_graph();
    }
};

class GraphFactory {
public:
    /* static AGraph* makeGraph(const std::string&, enum TASK); если без json */
    static AGraph* makeGraph(Json::Value&);

    virtual ~GraphFactory() = 0;
private:
    GraphFactory(){}
};

#endif
