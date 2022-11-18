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

		std::cout << "invalid data entries exist." << std::endl;

		for (size_t i = 0; i < problem.size(); i++) 
			std::cout << "problem exist at line " << problem[i].first << " entry " << problem[i].second << std::endl;
	
	} else {

		for (size_t i = 0; i < datavec.size(); i++) {
			int source = std::stoi(datavec[i][0]);
			int target = std::stoi(datavec[i][1]);
			int weight = std::stoi(datavec[i][2]);

			if (graph_.find(source) == graph_.end()) {
				graph_[source] = std::vector<std::pair<int,int>>();
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