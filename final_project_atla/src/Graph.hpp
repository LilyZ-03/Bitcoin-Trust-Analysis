/**
 * @file Graph.hpp
 * CS 225: Data Structures
 * Team Atla Final Project
 */

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

/**
 * Represents a graph.
 */
class Graph {
    public:
        /**
        * Constructs a graph from a given csv file.
        * @param filename A string containing the name of a csv file.
        */
        Graph(const std::string &filename);

        /**
        * Gets the graph member variable.
        * @return The stored graph.
        */
        std::map<int, std::vector<std::pair<int, int>>> getGraph() { return graph_; };

        /**
        * @param vertex The vertex for which the corresponding edges should be retrieved.
        * @return A vector of pairs, where the first value in the pair is the connected vertex and 
                the second value in the pair is the weight.
        */
        std::vector<std::pair<int, int>> getEdge(int vertex);

        /**
        * Gets the number of vertices in the graph.
        * @return The total number of vertices present in the graph. //this feels repetitive? it should be fine
        */
        int getNumVertices();

        /**
        * Performs DFS traversal on the graph.
        * Disconnect edges between vertices that are negative or not weighted highly enough according to a bound. 
        * Criteria: If edge is weighted at the bound or lower, weakly related.
        */
        void DFS();

        std::vector<std::set<int>> getSCC();
        std::set<int> getParentSCC(std::vector<std::set<int>>& scc, int v);
        std::map<int, std::vector<std::pair<int, int>>> getSCCGraph(std::vector<std::set<int>>& scc, int v);
        std::vector<std::pair<int, int>> dijkstra(std::map<int, std::vector<std::pair<int, int>>>& sccGraph, int start);
        std::set<int> getVertices();

    private:
        /**
        * Stores the graph.
        * Key: A given vertex.
        * Value: A vector of pairs where the first value in the pair is the connected vertex and 
                the second value in the pair is the weight.
        */
        std::map<int, std::vector<std::pair<int, int>>> graph_;
        
        /**
        * Bound used in DFS traversal to disconnect edges between vertices that have a weight equal or lower.
        */
        int BOUND_ = 2; 

        std::vector<std::vector<std::string>> parseData(const std::string &filename);
        void disconnect(int vertex);
        void DFSHelper(int vertex, std::set<int>& visited);
        void SCCHelper(int u, std::stack<int>& s); // u is the current vertex being processed
        int findClosest(std::vector<int>& dist, std::vector<bool> visited);
        int getEdgeWeight(std::map<int, std::vector<std::pair<int, int>>>& g, int u, int v);

        std::vector<int> disc; // Tarjan's
        std::vector<int> low; // Tarjan's
        std::vector<bool> stackMember; // Tarjan's
};