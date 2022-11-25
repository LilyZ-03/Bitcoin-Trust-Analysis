#include "Graph.hpp"

int main() {
    // std::cout << "Hi" << std::endl;

    std::string file = "../data/soc-sign-bitcoinotc.csv";
    Graph g(file);
    auto graph = g.getGraph();

    // for (auto i : graph) {
    //     std::cout << i.first << " " << i.second.size() << std::endl;
    // }

    g.DFS();

    graph = g.getGraph();
    
    for (auto i : graph) {
        std::cout << i.first << " weights: ";
        for (unsigned int j = 0; j < i.second.size(); j++) {
            std::cout << i.second.at(j).second << ", ";
        }
        std::cout << std::endl;
    }
    
    std::cout << g.getNumVertices() << std::endl; 

    // for (size_t i = 0; i < vec.size(); i++) {
    //     std::cout << vec[i][0] << " " << vec[i][1] << " " << vec[i][2] << " " << vec[i][3] << " " << std::endl;
    // }
}