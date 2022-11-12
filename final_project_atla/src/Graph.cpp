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

Graph::Graph() {}

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