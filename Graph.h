#include <vector>
#include <string>
class Graph {
	private:
		class Node {
			public:
				std::string name;
				int x;
				int y;
				Node(std::string name, int x, int y);
		};
		class Edge {
			public:
				int start;
				int end;
				int dist;
				Edge(int start, int end, int dist);
		};


	public:
		std::vector<Node> nodes;
		std::vector<Edge> edges;
		int addNode(std::string name, int x, int y);
		int addEdge(int start, int end, int dist);

};
