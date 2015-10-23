#ifndef AGRAPH
#define AGRAPH

#include <string>
#include <memory>
#include "../jsoncpp/include/json/json.h"

class AGraph {
    /* это реализация паттерна type erasure */
    struct GraphConcept {
        virtual bool algorithm() = 0;
        virtual ~GraphConcept() {}
    };

    template<typename T>
    struct GrapfModel : GraphConcept {
        GrapfModel( const T& t ) : object( t ) {}
        virtual bool algorithm() {
            return object.do_algorithm();
        }
        virtual ~GrapfModel() {}
    private:
        T object;
    };

private:
    std::unique_ptr<GraphConcept> object;

public:
    template<typename T>
    AGraph(const T& obj):object( new GrapfModel<T>( obj ) ) {}

    bool algorithm() {
        return object->algorithm();
    }
};

/* это паттерн фабричный метод, что-то вроде виртуального конструктора */
class GraphFactory {
public:
    //static AGraph* makeGraph(const std::string&, enum TASK); без json
    static AGraph* makeGraph(Json::Value&);

    virtual ~GraphFactory() = 0;
private:
    GraphFactory(){}
};

#endif
