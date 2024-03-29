/**
 * @file Graph.cpp
 *
 * Implementation of the Graph class.
 *
 * CS 225: Data Structures
 * Team Atla Final Project
 */

 #include "Graph.hpp"


// Helper function for data parsing, to process a line in the CSV file.
std::vector<std::string> parseLine(std::string line) {
	size_t l = 0, r = 0;
	std::vector<std::string> elems;
	for (r = 0; r < line.size(); r++) {
		if (line[r] == ',') {
			elems.push_back(line.substr(l, r - l));
			l = r + 1;
		}
	}
	elems.push_back(line.substr(l, r - l));
	return elems;
}

// Helper function to determine whether a string is convertible to a float/int number.
bool isNumber(std::string s) {
	bool decimalAppeared = false;
	for (size_t i = 0; i < s.size(); i++) {
		if (!std::isdigit(s[i])) {
			if (s[i] == '.') {
				if (!decimalAppeared) 
					decimalAppeared = true;
				else 
					return false;
				continue;
			}
			if (!(i == 0 && s[i] == '-'))
				return false;
		}
	}
	return true;
}

/* 
A helper function to perform data validation, will return a vector of all existing problems --
Each problem is represented as a pair where the first argument is the line index and the second argument is the type of problem.
*/
std::vector<std::pair<int, int>> dataValidation(std::vector<std::vector<std::string>> data) {
	std::vector<std::pair<int, int>> problem;
	for (size_t i = 0; i < data.size(); i++) {
		if (data[i].size() != 4) {
			problem.push_back(std::make_pair(i, 4));
		} else {
			if (!isNumber(data[i][0])) problem.push_back(std::make_pair(i, 0));

			if (!isNumber(data[i][1])) problem.push_back(std::make_pair(i, 1));
			
			if (isNumber(data[i][2])) {
				int n = std::stoi(data[i][2]);
				if (n < -10 || n > 10) problem.push_back(std::make_pair(i, 2));
			} else {
				problem.push_back(std::make_pair(i, 2));
			}

			if (!isNumber(data[i][3])) problem.push_back(std::make_pair(i, 3));
		}
	}
	return problem;
}

// Constructor. Data parsing and validation are both performed inside the constructor.
Graph::Graph(const std::string &filename) {
	auto datavec = parseData(filename);
	auto problem = dataValidation(datavec);

	if (problem.size() != 0) {

		throw "Invalid data entries exist.";

		for (size_t i = 0; i < problem.size(); i++) 
			throw "Problem exists at line " + std::to_string(problem[i].first);
	
	} else {

		for (size_t i = 0; i < datavec.size(); i++) {
			int source = std::stoi(datavec[i][0]);
			int target = std::stoi(datavec[i][1]);
			int weight = std::stoi(datavec[i][2]);

			if (graph_.find(source) == graph_.end()) {
				graph_[source] = std::vector<std::pair<int,int>>();
			} 
			if (graph_.find(target) == graph_.end()) {
				graph_[target] = std::vector<std::pair<int,int>>();
			}
			graph_[source].push_back(std::make_pair(target, weight));
		}

	}

}

// Helper function for data parsing.
std::vector<std::vector<std::string>> Graph::parseData(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<std::vector<std::string>> dataVec;
    std::string line;
    
    while (getline(file, line)) {
        dataVec.push_back(parseLine(line.substr(0, line.size() - 1)));
    }

    file.close();  
    return dataVec;
}

// Getter of the edges from the given vertex.
std::vector<std::pair<int, int>> Graph::getEdge(int vertex) {
	return graph_.at(vertex);
}

// Getter for the total number of vertices.
int Graph::getNumVertices() {
	return graph_.size();
}

// Deep-First Search algorithm, to disconnect edges below 
void Graph::DFS() {
	std::set<int> visited;
	// Call DFS on every vertex that hasn't been visited yet
	// to take care of unconnected components
	for (auto it = graph_.begin(); it != graph_.end(); it++) {
		if (visited.find(it->first) == visited.end()) {
			DFSHelper(it->first, visited);
		}
	}
}

// Recursive helper function for DFS traversal.
void Graph::DFSHelper(int vertex, std::set<int>& visited) {
	visited.insert(vertex);

	for (auto const& neighbor : graph_.at(vertex)) {
		if (visited.find(neighbor.first) == visited.end()) {
			DFSHelper(neighbor.first, visited);
		}
	}

	disconnect(vertex);
} 

// Disconnect edges between vertices that are negative or not weighted high enough.
// Criteria: If edge is weighted at the bound or lower, it is weakly related.
void Graph::disconnect(int vertex) {
	for (size_t i = 0; i < graph_.at(vertex).size(); i++) { // e is a pair <user id of the other user, weight of edge>
		if (graph_.at(vertex).at(i).second <= BOUND_) {
			graph_.at(vertex).erase(graph_.at(vertex).begin() + i);
			i--;  
		}
	}          
}

// Function to run Tarjan's algorithm & get strongly connected components.
std::vector<std::set<int>> Graph::getSCC() {
	std::vector<std::set<int>> scc;
	std::stack<int> s;
	
	disc.clear();
	low.clear();
	stackMember.clear();

	auto test_iter = graph_.end();
    test_iter--;

	int maxIDNumber = test_iter->first;

	for (int i = 0; i <= maxIDNumber; i++) { // Initialize all vectors with -1.
		disc.push_back(-1);
		low.push_back(-1);
		stackMember.push_back(false);
	}

	for (int i = 0; i <= maxIDNumber; i++) {
		if (disc.at(i) == -1 && graph_.find(i) != graph_.end()) {
			SCCHelper(i, s);
		}
	}

	std::map<int, std::set<int>> scc_map; 
	for (size_t i = 0; i < low.size(); i++) {
		if (low.at(i) != -1) {
			scc_map[low.at(i)].insert(i);
		}
	}

	for (auto p : scc_map) {
		if (p.second.size() > 1) {
			scc.push_back(p.second);
		}
	}

	return scc;
}

// Helper function for Tarjan's algorithm.
void Graph::SCCHelper(int u, std::stack<int>& s) { 
	static int time = 0;
	disc[u] = low[u] = ++time;
	s.push(u);
	stackMember[u] = true;

	for (auto it = graph_[u].begin(); it != graph_[u].end(); it++) {
		int v = it->first;
		if (disc[v] == -1) {
			SCCHelper(v, s);
			low[u] = std::min(low[u], low[v]);
		} else if (stackMember[v] == true) {
			low[u] = std::min(low[u], disc[v]);
		}
	}

	int w = 0;

	if (low[u] == disc[u]) {
		while (s.top() != u) {
			w = (int)s.top();
			stackMember[w] = false;
			s.pop();
		}
		w = (int) s.top();
		stackMember[w] = false;
		s.pop();
	}
}

// Get all the vertices in the SCC that vertice v belongs to.
// If vertex v does not belong to any SCC in this graph, an empty set is returned.
std::set<int> Graph::getParentSCC(std::vector<std::set<int>>& scc, int v) {
	for (size_t i = 0; i < scc.size(); i++) {
		if (scc.at(i).find(v) != scc.at(i).end()) 
			return scc.at(i);
	}

	return std::set<int>();
}

// Make a smaller graph from the old graph with all the vertices in the same SCC as the source vertex.
std::map<int, std::vector<std::pair<int, int>>> Graph::getSCCGraph(std::vector<std::set<int>>& scc, int v) {
	std::set<int> sccSet = getParentSCC(scc, v);
	if (sccSet.size() == 0) return std::map<int, std::vector<std::pair<int, int>>>();
	std::map<int, std::vector<std::pair<int, int>>> new_graph;
	for (int i : sccSet) {
		std::vector<std::pair<int, int>> new_edges;
		for (auto p : graph_.at(i)) {
			if (sccSet.find(p.first) != sccSet.end()) 
				// Inverse weight to obtain higher weighted trusts
				new_edges.push_back(std::make_pair(p.first, 11 - p.second)); 
		}
		new_graph[i] = new_edges;
	}
	return new_graph;
}

// Dijkstra's algorithm, to find the shortest path to all vertices in the SCC.
// In the result returned, first int in the pair is user id, second int is shortest path length.
std::vector<std::pair<int,int>> Graph::dijkstra(std::map<int, std::vector<std::pair<int, int>>>& sccGraph, int start) {
	std::vector<int> distance;
	std::vector<std::pair<int, int>> result;
	std::vector<bool> visited;
	std::map<int, int> oldToNewInd, newToOldInd;

	int count = 0;
	for (auto p : sccGraph) {
		oldToNewInd[p.first] = count;
		newToOldInd[count] = p.first;
		count++;
	}

	for (size_t i = 0; i < sccGraph.size(); i++) {
		distance.push_back(-1);  // Instead of INT_MAX
		visited.push_back(false);
	}

	distance.at(oldToNewInd[start]) = 0;
	
	for (size_t i = 0; i < sccGraph.size() - 1; i++) {
		/* u is the vertex that has the shortest distance from
		starting point in all the vertices that haven't been visited */
		int u = findClosest(distance, visited);
		visited[u] = true;

		for (size_t v = 0; v < sccGraph.size(); v++) {
			if (!visited[v]) {
				int weight = getEdgeWeight(sccGraph, newToOldInd[u], newToOldInd[v]);
				if (weight >= 0 && distance[u] >= 0 && (distance[v] < 0 || distance[u] + weight < distance[v]))
					distance[v] = distance[u] + weight;
			}
		}
	}

	for (size_t i = 0; i < distance.size(); i++) 
		result.push_back(std::make_pair(newToOldInd[i], distance[i]));

	return result;
}

// Helper function for Dijkstra's algorithm.
// Find the next vertex that should be visited by the algorithm.
int Graph::findClosest(std::vector<int>& dist, std::vector<bool> visited) {
	int minVal = -1, minInd;

	for (size_t i = 0; i < dist.size(); i++) {
		if ((dist[i] >= 0 && !visited[i]) && (minVal < 0 || dist[i] < minVal)) {
			minVal = dist[i];
			minInd = i;
		}
	}
	return minInd;
}

// Getter for the weight of the edge from u to v; if there doesn't exist an edge from u to v, the weight is -1.
int Graph::getEdgeWeight(std::map<int, std::vector<std::pair<int, int>>>& g, int u, int v) {
	auto edges = g.at(u);
	for (size_t i = 0; i <edges.size(); i++) {
		if (edges.at(i).first == v) return edges.at(i).second;
	}
	return -1;
}

// Getter for all the vertices in the graph, as a set of all user IDs.
std::set<int> Graph::getVertices() {
	std::set<int> s;

	for (auto pair : graph_) {
		s.insert(pair.first);
	}

	return s;
}