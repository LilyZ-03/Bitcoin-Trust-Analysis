#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Graph {
    public:
        Graph();
    private:
        std::map<int, std::vector<std::pair<int, int>>> graph_;
        std::map<int, std::vector<int>> adj_;
};