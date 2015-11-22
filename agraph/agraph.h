#include <string>
#include <memory>
#include <vector>
#include "../jsoncpp/include/json/json.h"

#include "agraph_export.h"

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


        virtual ~GraphModel() {}
    private:
        T object;
    };

    /* вот так можно восстановить объект */
/*
    template<typename U>
    U cast() const
    {

        if(typeid(U) != object->type_info())
            throw std::runtime_error("Bad graph cast");
        return static_cast<GraphModel<U>* >(object)->object;
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
class AGRAPH_EXPORT GraphFactory {
public:
    static AGraph* makeGraph(Json::Value&);
    static AGraph* makeGraph();
    static AGraph* makeGraph(string taskName);

    virtual ~GraphFactory() = 0;
private:
    GraphFactory(){}
};

