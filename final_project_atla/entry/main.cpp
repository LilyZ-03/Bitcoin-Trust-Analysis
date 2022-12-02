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
    
    // std::cout << g.getNumVertices() << std::endl; 

    // std::vector<std::set<int>> scc = g.getSCC();

    // for (size_t i = 0; i < scc.size(); i++) {
    //     std::string output = "";
    //     for (int entry : scc.at(i)) {
    //         output += std::to_string(entry) + " ";
    //     }
    //     std::cout << "scc " << i << ": " << output << std::endl;
    // }

    // for (size_t i = 0; i < vec.size(); i++) {
    //     std::cout << vec[i][0] << " " << vec[i][1] << " " << vec[i][2] << " " << vec[i][3] << " " << std::endl;
    // }
}