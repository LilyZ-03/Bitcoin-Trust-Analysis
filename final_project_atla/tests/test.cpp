#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "Graph.hpp"

TEST_CASE("Test Graph constructor - small", "[constructor]") {
     try {
        std::string file = "../data/tarjan-test1.csv";
        Graph g(file);
        auto graph = g.getGraph();

        int edge_count = 0;
        for (auto i : graph) {
            edge_count += i.second.size();
        }
        REQUIRE(edge_count == 18);

        // Test whether the graph was built properly by checking connections
        
        std::map<int, std::vector<std::pair<int, int>>> expected;

        expected[1] = {std::make_pair(2, 5), std::make_pair(3, 4), std::make_pair(4, 3)};
        expected[2] = {std::make_pair(3, 4)};
        expected[3] = {std::make_pair(1, 4), std::make_pair(7, -1)};
        expected[4] = {std::make_pair(7, 4), std::make_pair(1, -2)};
        expected[5] = {std::make_pair(6, 6), std::make_pair(8, 4), std::make_pair(10, 4)};
        expected[6] = {std::make_pair(9, 4), std::make_pair(10, 10)};
        expected[7] = {std::make_pair(1, 1)};
        expected[8] = {std::make_pair(5, 4)};
        expected[9] = {std::make_pair(5, 3)};
        expected[10] = {std::make_pair(5, 4), std::make_pair(6, 4)};

        for (int i = 1; i <= 10; i++) {
            REQUIRE(graph.at(i) ==  expected.at(i));
        }
    } catch(...) {
        REQUIRE(false);
    }
}

TEST_CASE("Test Graph constructor", "[constructor]") {
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

TEST_CASE("Test disconnect method on dummy graph", "[disconnect]") { 
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

TEST_CASE("Test disconnect method during DFS - small", "[dfs]") {
    try {
        std::string file = "../data/tarjan-test1.csv";
        Graph g(file);
        g.DFS();
        auto graph = g.getGraph();

        for (auto i : graph) {
            for (auto e : i.second) {
                REQUIRE(e.second > 2);
            }
        }
    } catch(...) {
        REQUIRE(false);
    }
}

TEST_CASE("Test disconnect method during DFS", "[dfs]") {
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

TEST_CASE("Test Tarjan's", "[dfs][tarjan]") {
    std::string file = "../data/tarjan-test1.csv";
    Graph g(file);
    g.DFS();
    std::vector<std::set<int>> scc = g.getSCC();

    REQUIRE(scc.size() == 2);

    std::set<int> scc1 {1,2,3};
    std::set<int> scc2 {5,6,8,9,10};

    REQUIRE(scc.at(0) == scc1);
    REQUIRE(scc.at(1) == scc2);
}

TEST_CASE("Test Dijkstra's", "[dfs][dijkstra]") {
    std::string file = "../data/tarjan-test1.csv";
    Graph g(file);
    g.DFS();
    std::vector<std::set<int>> scc = g.getSCC();
    
    std::map<int, std::vector<std::pair<int, int>>> sccGraph = g.getSCCGraph(scc, 1);
    std::vector<std::pair<int, int>> output = g.dijkstra(sccGraph, 1);

    // Subtract 11 from expected path lengths because of the inverse weighting strategy implemented in
    // our implementation of Dijkstra's algorithm.

    // Test 1st strongly connected component
    REQUIRE(output.at(1).first == 2);
    REQUIRE(abs(11 - output.at(1).second) == 5);

    REQUIRE(output.at(2).first == 3);
    REQUIRE(abs(11 - output.at(2).second) == 4);
    
    // Test 2nd strongly connected component
    sccGraph = g.getSCCGraph(scc, 10);
    output = g.dijkstra(sccGraph, 10);

    REQUIRE(output.at(0).first == 5);
    REQUIRE(abs(11 - output.at(0).second) == 4);

    REQUIRE(output.at(1).first == 6);
    REQUIRE(abs(11 - output.at(1).second) == 4);

    REQUIRE(output.at(2).first == 8);
    REQUIRE(abs(11 - output.at(2).second) == 3);

    REQUIRE(output.at(3).first == 9);
    REQUIRE(abs(11 - output.at(3).second) == 3);

}