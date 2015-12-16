#ifndef AGRAPH
#define AGRAPH

#include <string>
#include <memory>
#include "../jsoncpp/include/json/json.h"

#include "agraph_export.h"

/* 
это реализация паттерна type erasure
задача - скрыть объекты разных классов с общим интерфейсом за одним типом данных с тем же самым интерфейсом
решение - поскольку мы не можем менять структуру классов (они могут быть сторонними компонентами),
то мы используем обертку над каждым объектом, делегирующую ему вызовы методов. Все обертки наследуются от
одного класса, определяющего интерфейс.
*/

/* 
AGraph - обертка, скрывающая объекты за указателем.
Контейнеры stl хранят объекты по значению, поэтому если размещать в них объекты GraphConcept напрямую,
произойдет срезка. В данном случае она не особо нужна, так как в тестах можно использовать указатели.
*/
class AGraph {

	/* GraphConcept - общий интерфейc обобщенного класса граф */
    struct GraphConcept {
        virtual bool algorithm() = 0;
        virtual ~GraphConcept() {}
    };

	/* 
	GraphModel - реализация интерфейса на основе произвольного класса
	При этом от класса требуется не явное соответсвие какому-либо интерфейсу,
	а всего лишь наличие подходящих методов, иногда это называют неявной спецификацией. 
	Например, bool algorithm() может вызывать X object.do_algorithm(), если определено
	приведение типа T::operator bool() и т.п.
	*/
    template<typename T>
    struct GraphModel : GraphConcept {
        GraphModel( const T& t ) : object( t ) {}
        virtual bool algorithm() {
            return object.do_algorithm();
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

    bool algorithm() {
        return object->algorithm();
    }
};

/* это паттерн фабричный метод, что-то вроде виртуального конструктора */
/* 
атрибут PROJECT_EXPORT явно указывает, что этот интерфейс библиотеки доступен для вызова из другого места.
без него под MSVC приложение не соберется
*/
class AGRAPH_EXPORT GraphFactory {
public:
    /* static AGraph* makeGraph(const std::string&, enum TASK); если без json */
    static AGraph* makeGraph(Json::Value&);

    virtual ~GraphFactory() = 0;
private:
    GraphFactory(){}
};

#endif
