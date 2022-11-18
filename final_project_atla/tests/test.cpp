#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include "Graph.hpp"

TEST_CASE("test Graph constructor") {

    std::string file = "../data/soc-sign-bitcoinotc.csv";
    Graph g(file);
    auto graph = g.getGraph();

    bool valid = true;
    for (auto i : graph) {
        if (i.second.size() == 0) valid = false;
    }
  
    REQUIRE(valid);
}