#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <unordered_map>
#include <map>
#include <list>
#include <memory>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <iterator>
#include <fstream>
#include <exception>
#include <stack>
#include <queue>

using namespace std;

enum class color{ white, black, gray };
template <class type> class vertex;
template <class type, class E> class edge;
template <class type, class E> class graph_list;

template <class type, class E>
class edge{
private:
	friend class graph_list <type, E>;
	friend class vertex <type>;

	shared_ptr <vertex<type>> vertex_to;
	shared_ptr <vertex<type>> vertex_from;
    E weigh;
public:
	edge() {
		vertex_to = nullptr;
		vertex_from = nullptr;
		weigh = 0;
	}
	edge(shared_ptr<vertex<type>> from, shared_ptr <vertex<type>> to, E weigh) {
		vertex_to = to;
		vertex_from = from;
		this->weigh = weigh;
	}
public:
	void print_edge() {
		cout << "Edge : ";
		cout << "From : " << vertex_from->name << "; To : " << vertex_to->name << "; Weigh == " << weigh << endl;
		return;
	}

};


//**********Vertex class***********//
template <class type>
class vertex{
	
	template <class Type, class Edge>
	friend class graph_list;
	template <class Type>
	friend class time_out_comparator;
	template <class Type, class Edge>
	friend class edge;
private:
	unordered_map <string, shared_ptr <vertex <type>>> vertices_to;		
	unordered_map <string, shared_ptr <vertex <type>>> vertices_from;	

	void add_way_to(string name, shared_ptr <vertex<type>> pointer) {
		vertices_to[name] = shared_ptr <vertex<type>>{ pointer };
		return;
		// then update edges.
	};
	void add_way_from(string name, shared_ptr <vertex<type>> pointer) {
		vertices_from[name] = shared_ptr <vertex<type>>{ pointer };
		return;
		// then I nust update edges. I'll do it later;
	}

	string name;
	type data;
	
//DFS	
	color current_color;					//Детали DFS
	size_t thelowestlink;
	size_t time_in;
	size_t time_out;
//DFS

public:
	vertex() {
		name = "noname";
		data = 0;
		current_color = color::white;
		time_in = -1;
		time_out = -1;
	}
	vertex(const string& name) {
		this->name = name;
		data = 0;
		current_color = color::white;
		time_in = -1;
		time_out = -1;
	}
	
	void set_name(const string& name){
		this->name = name;
	}
	void set_color(const color& our_color) {
		this->current_color = our_color;
	}
	
	string get_name() {
		return name;
	}
	type get_data() {
		return data;
	}
	color get_color() {
		return current_color;
	}

	unordered_map <string, shared_ptr <vertex <type>>> get_map_to() {
		return vertices_to;
	}
	unordered_map <string, shared_ptr <vertex <type>>> get_map_from() {
		return vertices_from;
	}

	void print_vertex() {
		cout << "Vertex " << name << "."/* << endl << "Data : " << data*/ << "; Time_in: " << time_in << "; Time_out: " << time_out;
		if (current_color == color::white) cout << "; Color : white";
		if (current_color == color::gray)  cout << "; Color : gray";
		if (current_color == color::black) cout << "; Color : black";
		cout << endl;
	}
	void print_vertex_ways() {
		cout << "Ways to : ";
		for (const auto &kvp : vertices_to) {
			cout << kvp.first << " ";
		}
		cout << endl << "Ways from : ";
		for (const auto &kvp : vertices_from) {
			cout << kvp.first << " ";
		}
		cout << endl;
	}
};

template <class type>
class time_out_comparator {
public:
	bool operator()(const vertex <type>& v1, const vertex <type>& v2) {
		return v1.time_out < v2.time_out;
	}
	bool operator()(const std::pair<string, vertex <type>>& pair1, const std::pair <string, vertex <type>>& pair2) {
		return pair1.second.time_out < pair2.second.time_out;
	}
	bool operator()(const std::pair<string, shared_ptr<vertex<type>>>& pair1, const std::pair<string, shared_ptr<vertex<type>>>& pair2) {
		return (pair1.second->time_out) < pair2.second->time_out;
	}
	bool operator()(const shared_ptr <vertex<type>>& ptr1, const shared_ptr <vertex<type>>& ptr2) {
		return ptr1->time_out < ptr2->time_out;
	}
};

template <class type, class E>
class graph_list
{
private:
	unordered_map <string, shared_ptr <vertex <type>>> vertices;
	vector <shared_ptr <vertex<type>>> pvertices;
	
	unordered_map<string, unordered_map<string, shared_ptr <edge <type, E>>>> edges;//[]

	int vertices_number;

	int timer;
	bool tree;			//Если это было дерево обхода, то true, иначе - false

	void whitewash_all() {
		for (auto& it : vertices) {
			it.second->current_color = color::white;
		}
	}
	void zero_numbers() {
		for (auto& it : vertices) {
			it.second->time_in = 0;
			it.second->time_out = 0;
			it.second->thelowestlink = 0;
		}
	}
	bool vertex_in_graph(const string& name)
	{
		for (const auto& it : vertices) {
			if (it.first == name) return true;
		}
		return false;
	}
public:
	graph_list() {
		vertices_number = 0;
		timer = 0;
	};

	void insert_vertex(const string& name) {
		if (!vertex_in_graph(name)) {
			auto ptr = make_shared <vertex<type>>(name);
			vertices[name] = ptr;
			pvertices.push_back(ptr);
		}
		return;
	}

	double get_weigh(const string& from, const string& to) {
		if (vertex_in_graph(from) && vertex_in_graph(to))
			return edges[from][to].weigh;
		else {
			cout << "No such vertex" << endl;
		}
	}

	void print_graph() {
		cout << "You called function that prints all graph as lists. Now we're starting:" << endl;
		for (const auto &it : vertices) {
			cout << "Vertex : " << it.first << "; Ways to : ";
			for (const auto &kvp : it.second->vertices_to) {
				cout << kvp.first << " ";
			}
			cout << "; Ways from : ";
			for (const auto &kvp : it.second->vertices_from) {
				cout << kvp.first << " ";
			}
			cout << endl;
		}
		cout << "printed_successfully\n";
	}

	void insert_vertices(const vector <vertex <type>>& vertices_to_insert) {
		for (auto& it : vertices_to_insert) {
			if (!vertex_in_graph(it.name)) {
				insert_vertex(it.name);
			}
		}
		return;
	};

	void add_edge(const string& from, const string& to, E weigh = 0) {
		if (!vertex_in_graph(from) || !vertex_in_graph(to)) //Если в графе нет хотя бы одной из указанных вершин, вставка не удастся
			return;

		auto v_from = vertices[from];		//Here are the pointers to vertices with names from and to
		auto v_to = vertices[to];
		edge <type, E> Edge{ v_from, v_to, weigh };
		edges[from][to] = make_shared <edge <type, E>>(Edge);
		v_from->add_way_to(to, v_to);//What did I wrote here?
		v_to->add_way_from(from, v_from);		//Here I'm adding to and from vertices to theirs lists "to" and "from"
	}

	vertex <type> operator[](const string& name) {
		if (!vertex_in_graph(name)) {
			for (const auto& it : vertices) {
				if (it.first == name) 
					return it.second;
			}
		}
	}

	void transpose() {
		for (auto& it : vertices) {
			auto v_pointer = (it.second);
			v_pointer->vertices_to.swap(v_pointer->vertices_from);
		}
	}
	
	vector <vector <string>> Kosaraju() {
		top_sort();
		transpose();

		std::sort(pvertices.rbegin(), pvertices.rend(), *(new time_out_comparator<type>{})); 
		top_sort();


		//Working with log file, we are catching strong-connected components from it
		fstream log("dfs_for_top.log", ios :: in);
		string line;
		bool prev_left = false;
		vector <vector <string>> answer;

		size_t strong_connected_index = -1;
		while (!log.eof()) {
			getline(log, line);
			if (line[0] == 't') 
				continue;//If current line begins with "tried" - we must skip it
			//
			size_t left_position = line.find("left");
			
			if (left_position < 1000) {
				if (!prev_left) {
					answer.push_back(*(new vector<string>));
					strong_connected_index++;
				}
				string name = line.substr(left_position + string("line ").size(), line.size() - 1);
				answer[strong_connected_index].push_back(name);
				prev_left = true;
			}
			else prev_left = false;
		}

		return answer;
	};

	void dfs_for_Tarjan(shared_ptr <vertex <type>>& pvertex, fstream& log_file, vector<vector<string>>& answer) {
		static stack <shared_ptr<vertex<type>>> Stack;
		if (pvertex->current_color == color::white) {	
			Stack.push(pvertex);//pushing vertex on stack
			pvertex->thelowestlink = timer;//the lowest time from vertices from which this vertex can be reached OR making the lowestlink
			log_file << "dfs timer == " << (pvertex->time_in = timer++) << " joined " << pvertex->name << endl; //writing log
			pvertex->current_color = color::gray;//mark vertex as already visited
		}
		else {
			log_file << "tried to join vertex " << pvertex->name << ", but failed : color == " << ((pvertex->current_color == color::gray) ? "gray" : "black") << endl;
			return;
		}

		for (auto& ptr : pvertex->vertices_to) {
			if (ptr.second->current_color == color::white) {
				dfs_for_Tarjan(ptr.second, log_file, answer);	//ptr.second is a vertex in the list of vertices_to of vertex *pvertex
				pvertex->thelowestlink = min(pvertex->thelowestlink, ptr.second->thelowestlink);
			}
			else {
				if (ptr.second->current_color == color::gray) {
					pvertex->thelowestlink = min(pvertex->thelowestlink, ptr.second->time_in);
				}
				log_file << "tried to join vertex " << pvertex->name << ", but failed : color == " << ((pvertex->current_color == color::gray) ? "gray" : "black") << endl;
			}
		}


		if (pvertex->thelowestlink == pvertex->time_in) {//That is mean that it is a root of s strongly connected component
			shared_ptr <vertex<type>> vrtx;
			vector <string> component;
			do
			{
				vrtx = Stack.top();
				Stack.pop();
				vrtx->current_color = color::black;
				component.push_back(vrtx->name);
			} while (vrtx != pvertex);
			answer.push_back(component);
		}
		return;
	};

	vector <vector<string>> Tarjan() {
		whitewash_all();
		zero_numbers();
		fstream log_file;
		vector <vector<string>> answer;
		log_file.open("dfs_for_Tarjan.log", ios::trunc | ios_base::out);
		timer = 0;

		auto& it = pvertices.begin();
		log_file << "dfs_for_Tarjan started from vertex " << (*it)->name << endl;
		for (auto& it : vertices) {
			dfs_for_Tarjan(it.second, log_file, answer);
		}
		return answer;
	}

	void dfs_for_top(shared_ptr <vertex<type>>& pvertex, fstream& log_file) {
		if (pvertex->current_color == color::gray || pvertex->current_color == color::black) {
			log_file << "tried to join vertex " << pvertex->name << ", but failed : color == " << ((pvertex->current_color == color::gray) ? "gray" : "black") << endl;
			return;
		}

		log_file << "dfs timer == " << (pvertex->time_in = timer++) << " joined " << pvertex->name << endl;
		pvertex->current_color = color::gray;

		for (auto& ptr : pvertex->vertices_to) {//Проходимся по всем соседям вершины графа vertex, ptrs - итератор map<string, shared_ptr> соседей вершины
			dfs_for_top(ptr.second, log_file);
		}

		log_file << "dfs timer == " << (pvertex->time_out = timer++) << " left " << pvertex->name << endl;
		pvertex->current_color = color::black;
		return;
	}
	
	void top_sort() {

		whitewash_all();	//Красим все вершины в белый цвет
		zero_numbers();		//Zero all vertices time_out and time_in

		auto it = pvertices.begin();
		fstream log_file;
		log_file.open("dfs_for_top.log", ios::trunc | ios_base::out);

		timer = 0;
		log_file << "dfs_for_top started from vertex " << (*it)->name << endl;
		for (auto& it : pvertices) { 
			dfs_for_top(it, log_file);
		}
		log_file << "Top_sort finished...\n\n\n\n\n\n\n\n\n\n";
		log_file.close();
	}

	void Ford_Bellman(const string& name) {
		for (const auto& it : edges) {
			for (const auto& jt : it.second) {
				jt.second->print_edge();
			}
		}
	}

};



#endif
