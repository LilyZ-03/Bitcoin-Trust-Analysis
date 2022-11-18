#include "Graph.hpp"
#include <fstream>

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

Graph::Graph(const std::string &filename) {
	auto datavec = parseData(filename);
	auto problem = dataValidation(datavec);

	if (problem.size() != 0) {

		// std::cout << "invalid data entries exist." << std::endl;
		throw "Invalid data entries exist.";

		for (size_t i = 0; i < problem.size(); i++) 
			// std::string message = "Problem exists at line " + problem[i].first;
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

void Graph::DFSHelper(int vertex, std::set<int>& visited) {
	visited.insert(vertex);

	for (auto const& neighbor : graph_.at(vertex)) {
		if (visited.find(neighbor.first) == visited.end()) {
			DFSHelper(neighbor.first, visited);
		}
	}

	disconnect(vertex);
} 

// Disconnect edges between vertices that are negative or not weighted high enough
// Criteria: If edge is weighted at the bound or lower, weakly related
void Graph::disconnect(int vertex) {
	for (size_t i = 0; i < graph_.at(vertex).size(); i++) { // e is a pair <user id of the other user, weight of edge>
		if (graph_.at(vertex).at(i).second <= BOUND_) {
			graph_.at(vertex).erase(graph_.at(vertex).begin() + i);
			i--;  
		}
	}          
}