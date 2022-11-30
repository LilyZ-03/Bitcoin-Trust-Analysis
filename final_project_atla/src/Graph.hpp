#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <stack>
#include <fstream>
#include <algorithm>

class Graph {
    public:
        Graph(const std::string &filename);
        std::map<int, std::vector<std::pair<int, int>>> getGraph() { return graph_; };
        std::vector<std::pair<int, int>> getEdge(int vertex);
        int getNumVertices();
        void DFS();
        
        std::vector<std::set<int>> getSCC();
        void SCCHelper(int u, std::stack<int>& s); // u is the current vertex being processed

    private:
        // in the pair, the first int is the destination, the second int is the weight
        // User id (vertex) = int
        // Edges connected to vertex (<user id of the other user, weight of edge>) = vector of pairs: 
        std::map<int, std::vector<std::pair<int, int>>> graph_;
        int BOUND_ = 2;

        std::vector<std::vector<std::string>> parseData(const std::string &filename);
        void disconnect(int vertex);
        void DFSHelper(int vertex, std::set<int>& visited);

        std::vector<int> disc; // Tarjan's
        std::vector<int> low; // Tarjan's
        std::vector<bool> stackMember; // Tarjan's
};