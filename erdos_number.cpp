#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

class Node {
	private:
		int number;
		bool visited;
	public:
		Node() {
			number = 1;
			visited = false;
		}
		int get_number() {
			return number;
		}
		bool get_visited() {
			return visited;
		}
		void set_number(int n){
			number = n;
		}
		void set_visited() {
			visited = true;
		}
		void reset_visited() {
			visited = false;
		}
};

namespace io_functions {

	int read_info() {
		int info;
		std::cin >> info;
		return info;
	}

	void display_result(int max_distance, std::vector<int> &output) {
		std::cout << max_distance << std::endl;
		for (int i = 1; i <= max_distance; i++) {
			std::cout << output.at(i) << std::endl;
		}
	}
}

namespace graph_functions {

	void insert_connection(int author_1, Node * author_2, std::vector<std::list<Node*> > &graph) {
		graph.at(author_1).push_front(author_2);
	}

	void build_graph(std::vector<std::list<Node*> > &graph, std::vector<Node*> &node_vector, int n_connections) {
		int author_1, author_2;
		for (int i = 0; i < n_connections; i++) {
			author_1 = io_functions::read_info();
			author_2 = io_functions::read_info();
			insert_connection(author_1, node_vector.at(author_2), graph);
			insert_connection(author_2, node_vector.at(author_1), graph);
		}
	}


	void calculate_distance(std::vector<std::list<Node*> > &graph, std::queue<int> &queue, std::vector<Node*> &node_vector,	
	     std::vector<int> &distance) {
		Node* reached_vertex;
		Node* beginning_vertex;
		int n_beginning_vertex;
		int dist;

		while (! (queue.empty()) ) {
			beginning_vertex = node_vector.at(queue.front());
			n_beginning_vertex = beginning_vertex->get_number();
			dist = distance.at(n_beginning_vertex) + 1 ;
			queue.pop();

			while (! (graph.at(n_beginning_vertex).empty()) ) {		//enquanto a lista de vertices não estiver vazia
				reached_vertex = graph.at(n_beginning_vertex).front();    //guardar vertice alcancado
				graph.at(n_beginning_vertex).pop_front();                  //retirar vertice alcancado da lista
				if (! (reached_vertex->get_visited()) ) {		//se vertice nao foi visitado
					reached_vertex->set_visited();		 // marcar o vertice alcancado
					distance.at(reached_vertex->get_number()) = dist;    //atribuir distancia ao vertice alcancado
					queue.push(reached_vertex->get_number());		//colocar vertice alcancado na fila
				}
			}
		}
	}

	void counting (std::vector<int> &distance, std::vector<int> &output, int n_vertexes) {
		for (int i = 1; i <= n_vertexes; i++) {
			output.at(distance.at(i)) ++;
		}
	}
}

int main () {

	int n_vertexes = io_functions::read_info();
	int n_connections = io_functions::read_info();
	int beginning_vertex = io_functions::read_info();

	/*criação e inicializacao do vetor de nos*/
	std::vector<Node*> node_vector (n_vertexes + 1);
	node_vector.at(0) = NULL;
	for (int i = 1; i <= n_vertexes; i++) {
		node_vector.at(i) = new Node();
		node_vector.at(i)->set_number(i);
	}

	std::vector<std::list<Node*> > graph (n_vertexes + 1);
	graph_functions::build_graph(graph, node_vector, n_connections);

	std::queue<int> queue;

	queue.push(beginning_vertex);
	node_vector.at(beginning_vertex)->set_visited();
	std::vector<int> distance (n_vertexes + 1, 0);

	graph_functions::calculate_distance(graph, queue, node_vector, distance);

	int max_distance = *std::max_element(distance.begin(), distance.end() );

	std::vector<int> output (max_distance + 1, 0);

	graph_functions::counting(distance, output, n_vertexes);

	io_functions::display_result(max_distance, output);

	for (int i = 1; i <= n_vertexes; i++) {
		delete node_vector.at(i);
	}
	return 0;
}


