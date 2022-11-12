#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

class Graph {
    public:
        Graph();
        std::vector<std::vector<std::string>> parseData(const std::string &filename);

    private:
        std::map<int, std::vector<std::pair<int, int>>> graph_;
        std::map<int, std::vector<int>> adj_;
};