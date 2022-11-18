#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "Graph.hpp"

TEST_CASE("Test Graph constructor") {
    
    try {
        std::string file = "../data/soc-sign-bitcoinotc.csv";
        Graph g(file);
        auto graph = g.getGraph();

        int edge_count = 0;
        for (auto i : graph) {
            edge_count += i.second.size();
        }
        REQUIRE(edge_count == 35592);
    } catch(...) {
        REQUIRE(false);
    }

}

TEST_CASE("Test disconnect method on dummy graph") {
    
    std::map<int, std::vector<std::pair<int, int>>> dummy = std::map<int, std::vector<std::pair<int, int>>>();
    dummy[0] = {std::make_pair(1,4), std::make_pair(2,1), std::make_pair(3,-1), std::make_pair(1,-10)};
    dummy[1] = {std::make_pair(1,-10), std::make_pair(2,10)};
    dummy[2] = {std::make_pair(1,0), std::make_pair(2,2)};
    dummy[3] = {std::make_pair(1,8), std::make_pair(2,3)};
    dummy[4] = {std::make_pair(1,-10), std::make_pair(2,-5)};

    int vertex = 0;
    for (size_t i = 0; i < dummy.at(vertex).size(); i++) {
		if (dummy.at(vertex).at(i).second <= 2) {
			dummy.at(vertex).erase(dummy.at(vertex).begin() + i);
			i--;
		}
	}
    REQUIRE(dummy.at(vertex).size() == 1);

    vertex = 1;
    for (size_t i = 0; i < dummy.at(vertex).size(); i++) {
		if (dummy.at(vertex).at(i).second <= 2) {
			dummy.at(vertex).erase(dummy.at(vertex).begin() + i);
			i--;
		}
	}
    REQUIRE(dummy.at(vertex).size() == 1);

    vertex = 2;
    for (size_t i = 0; i < dummy.at(vertex).size(); i++) {
		if (dummy.at(vertex).at(i).second <= 2) {
			dummy.at(vertex).erase(dummy.at(vertex).begin() + i);
			i--;
		}
	}
    REQUIRE(dummy.at(vertex).size() == 0);

    vertex = 3;
    for (size_t i = 0; i < dummy.at(vertex).size(); i++) {
		if (dummy.at(vertex).at(i).second <= 2) {
			dummy.at(vertex).erase(dummy.at(vertex).begin() + i);
			i--;
		}
	}
    REQUIRE(dummy.at(vertex).size() == 2);

    vertex = 4;
    for (size_t i = 0; i < dummy.at(vertex).size(); i++) { 
		if (dummy.at(vertex).at(i).second <= 2) {
			dummy.at(vertex).erase(dummy.at(vertex).begin() + i);
			i--;
		}
	}
    REQUIRE(dummy.at(vertex).size() == 0);
}

TEST_CASE("Test disconnect method during DFS") {
    std::string file = "../data/soc-sign-bitcoinotc.csv";
    Graph g(file);
    g.DFS();
    auto graph = g.getGraph();

    for (auto i : graph) {
        for (unsigned int j = 0; j < i.second.size(); j++) {
            // Make sure all weights are above bound
            REQUIRE(i.second.at(j).second > 2);
        }
    }
}

