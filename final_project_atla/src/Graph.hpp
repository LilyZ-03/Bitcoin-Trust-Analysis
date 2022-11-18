#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Graph {
    public:
        Graph(const std::string &filename);
        std::map<int, std::vector<std::pair<int, int>>> getGraph() { return graph_; };

    private:
        // in the pair, the first int is the destination, the second int is the weight
        std::map<int, std::vector<std::pair<int, int>>> graph_;
        std::map<int, std::vector<int>> adj_;

        std::vector<std::vector<std::string>> parseData(const std::string &filename);
};