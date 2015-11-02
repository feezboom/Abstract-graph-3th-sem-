#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include "graph.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Hello world! I'm started my work." << endl;

	fstream in;													
    vertex <int> v;
	string name, current_name;									
	graph_list <int, double> our_graph;							
	shared_ptr <vertex <int>> ptr;								
	size_t vertices_number, vertex_count;						
	vector <vertex <int>> vertices;

	in.open("test_graph.txt");
	if (!in) {
		in.open("../test_graph.txt");
		if (!in) {
			cout << "file test_graph.txt was not found" << endl;
			exit(1);
        }
	} 	
	in >> vertices_number;										

																
	for (size_t i = 0; i < vertices_number; i++){
		in >> name;
		vertices.push_back(vertex <int> (name));
	}

	our_graph.insert_vertices(vertices);						
																
	for (size_t i = 0; i < vertices_number; i++)
	{
		in >> name;												
		in >> vertex_count;										
																
		for (size_t i = 0; i < vertex_count; i++)
		{
			double weigh;
			in >> current_name;
			in >> weigh; 
			our_graph.add_edge(name, current_name, weigh);
		}
	}
	
//	our_graph.insert_vertex("Fuck");

	//int* q = new int(24);
	//shared_ptr <int> p(new int(10));
	//shared_ptr <int> p1(p);
	//shared_ptr <int> p2(q);
	//cout << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ --->>> " << *p2 << endl;

	//vertex <int> a{ "shit" };
	//shared_ptr <vertex<int>> s = make_shared <vertex<int>>(a);
	//a.set_name("motherfucker");
	//s->set_name("unit");

//	our_graph.insert_vertex(a);
	
	our_graph.add_edge("Fuck", "motherfucker");

//	our_graph.top_sort();
//	our_graph.print_graph();									

	vector<vector<string>> ans = our_graph.Kosaraju();
//	vector <vector<string>> ans = our_graph.Tarjan();
	
	our_graph.transpose();
	our_graph.print_graph();

	cout << "Strong connected components are:" << endl;
	for (const auto& i : ans) {
		for (const auto& j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
//	try {
////		unordered_map <string, double> ford_bellban = our_graph.Ford_Bellman("v1");
//	}
//	catch (const exception& ex) {
//		cerr << ex.what();
//	}

//	our_graph.Ford_Bellman("v1");
	
	cout << "Hey, program finished its work;)\n";
	return 0;
}
