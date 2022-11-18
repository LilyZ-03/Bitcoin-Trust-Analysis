#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <set>

class Graph {
    public:
        Graph(const std::string &filename);
        std::map<int, std::vector<std::pair<int, int>>> getGraph() { return graph_; };
        void DFS();

    private:
        // in the pair, the first int is the destination, the second int is the weight
        // User id (vertex) = int
        // Edges connected to vertex (<user id of the other user, weight of edge>) = vector of pairs: 
        std::map<int, std::vector<std::pair<int, int>>> graph_;
        std::map<int, std::vector<std::pair<int, int>>> adj_;
        int BOUND_ = 2;

        std::vector<std::vector<std::string>> parseData(const std::string &filename);
        void disconnect(int vertex);
        void DFSHelper(int vertex, std::set<int>& visited);
        
};